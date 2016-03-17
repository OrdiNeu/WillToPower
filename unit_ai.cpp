#include "unit_ai.hpp"
// using namespace std;

AI::AI(Unit* controlled, Map* curMap) : controlled(controlled), curMap(curMap) {
	timeSinceLastUpdate = UNIT_AI_UPDATE_TIME;
	lastKnownPos = Map::TexXYToTileXY(controlled->realX, controlled->realY);
}

bool AI::isUnitCloseToCenterOfTile(point* unitLoc) {
#ifdef AI_MOVE_CENTER_OF_TILE
	point* centerPoint = Map::TileXYToTexXY(unitLoc->tileX, unitLoc->tileY);
	float dx = controlled->realX - centerPoint->realX;
	float dy = controlled->realY - centerPoint->realY;
	delete centerPoint;
	return dx * dx + dy * dy < DISTANCE_FROM_CENTER_SQ;
#else
	return true;
#endif
}

bool AI::walkToPoint(point* targetPoint, point* curPoint, int distance_allowed) {
	if (targetPoint == NULL) {
		// Can't do anything with this
		return false;
	}

	if (curPoint == NULL) {
		curPoint = Map::TexXYToTileXY(controlled->realX, controlled->realY);
	}

	std::vector<point*> route = AStarSearch(curMap, curPoint->tileX, curPoint->tileY, targetPoint->tileX, targetPoint->tileY, 1);
	if (route.size() != 0) {
		// Remove the last point in the route, since it is the current position
		point* last_point = route.back();
		delete last_point;
		route.pop_back();

		// Walk to the target location
		controlled->walkTo(route);
		return true;
	}

	return false;
}

void AI::cancelJob(Job* job, std::string reason) {
	std::cerr << "Job suspended: " << reason << std::endl;
	jobState = 0;
	controlled->state = STATE_IDLE;
	job->suspended = true;
}

// Cause the controlled unit to move to the next point on its list
void AI::moveToNextPoint() {
	point* last_point = controlled->curPath.back();
	delete last_point;
	controlled->curPath.pop_back();
}

void AI::continueWalking() {
	point* curPos = Map::TexXYToTileXY(controlled->realX, controlled->realY);
	if (curPos->tileX != lastKnownPos->tileX || curPos->tileY != lastKnownPos->tileY) {
		if (isUnitCloseToCenterOfTile(curPos)) {
			// Are we at the target location?
			point* nextLoc = controlled->curPath.back();
			if (curPos->tileX != nextLoc->tileX || curPos->tileY != nextLoc->tileY) {
				std::cout << "Unit ended up somewhere unexpected - need to recreate path" << std::endl;
				std::cout << "(Expected " << nextLoc->tileX << "," << nextLoc->tileY << "), got (" << curPos->tileX << "," << curPos->tileY << "))" << std::endl;
				std::cout << "Last known position:" << lastKnownPos->tileX << "," << lastKnownPos->tileY << std::endl;
				// We meed to recreate the path
				int targetX, targetY;
				while (!controlled->curPath.empty()) {
					point* pathPoint = controlled->curPath.back();
					targetX = pathPoint->tileX;
					targetY = pathPoint->tileY;
					controlled->curPath.pop_back();
					delete pathPoint;
				}
				controlled->curPath = AStarSearch(curMap, curPos->tileX, curPos->tileY, targetX, targetY);
			}
			moveToNextPoint();
			lastKnownPos->tileX = curPos->tileX;
			lastKnownPos->tileY = curPos->tileY;
		}
	}
	delete curPos;
}

bool AI::meetsJobRequirements(Job job) {
	// Can't pick up a suspended job
	if (job.suspended) {
		return false;
	}

	// Can't pick up jobs that are assigned to someone else
	if (!(job.assigned == NULL || job.assigned == controlled)) {
		return false;
	}

	// Can't pick up jobs we're not qualified for
	if ((job.requirements & controlled->skills) != job.requirements) {
		return false;
	}

	return true;
}

bool AI::checkJobBoard() {
	// Check the job board for stuff to do
	int jobPicked = -1;
	for (unsigned int i = 0; i < JobQueue::jobQueue.size(); i++) {
		Job job = JobQueue::jobQueue[i];

		if (!meetsJobRequirements(job)) {
			continue;
		}

		// Passed all checks: determine what to do depending on the type of job
		point* curPoint = Map::TexXYToTileXY(controlled->realX, controlled->realY);
		lastKnownPos->tileX = curPoint->tileX;
		lastKnownPos->tileY = curPoint->tileY;
		std::vector<point*> route;
		point* targetPoint;
		switch(job.type) {
			case JOB_TYPE_MINING: {
				if (job.targetPoint == NULL) {
					std::cerr << "Error: mining job created without a target point" << std::endl;
					continue;
				}
				targetPoint = job.targetPoint;
				break;
			}
			case JOB_TYPE_WOODCUT: {
				if (job.targetEnt == NULL) {
					std::cerr << "Error: woodcut job created without a target ent" << std::endl;
					continue;
				}
				targetPoint = Map::TexXYToTileXY(job.targetEnt->realX, job.targetEnt->realY);
				break;
			}
			case JOB_TYPE_BUILD: {
				if (job.targetEnt == NULL || ((Item*) job.targetEnt)->inInventory == true) {
					cancelJob(&(job), "item destroyed or missing");
					continue;
				} else if (job.targetPoint == NULL) {
					std::cerr << "Error: building job created without a target point" << std::endl;
					continue;
				} 
				targetPoint = Map::TexXYToTileXY(job.targetEnt->realX, job.targetEnt->realY);
				break;
			}
		}

		// Pathfind to the job and pick it up
		if (walkToPoint(targetPoint, curPoint, 1)) {
			curJob = job;
			JobQueue::jobQueue.erase(JobQueue::jobQueue.begin() + jobPicked);
			job.assigned = controlled;
			jobState = JOB_STAGE_WALKING_TO_DEST;
			delete curPoint;
			return true;
		} else {
			cancelJob(&(job), "could not reach target");
		}
		delete curPoint;
	}
	return false;
}

void AI::finishJob() {
	jobState = 0;
	controlled->state = STATE_IDLE;
	switch(curJob.type) {
		case JOB_TYPE_MINING: {
			if (curJob.targetPoint != NULL) {
				curMap->setTasked(curJob.targetPoint->tileX,curJob.targetPoint->tileY, false);
				curMap->setColor(curJob.targetPoint->tileX,curJob.targetPoint->tileY, COLOR_NONE);
			}
			break;
		}
		case JOB_TYPE_WOODCUT: {
			if (curJob.targetEnt == NULL) {
				cancelJob(&(curJob), "target destroyed or missing");
				return;
			}
			RequestQueues::entityRequests.push_back(entRequest::newEntRequest("Wood", curJob.targetEnt->realX, curJob.targetEnt->realY, ENT_TYPE_ITEM));
			RequestQueues::entityRequests.push_back(entRequest::delEntRequest(curJob.targetEnt->uid, ENT_TYPE_DOODAD));
			break;
		}
		case JOB_TYPE_BUILD: {
			if (curJob.targetEnt == NULL) {
				cancelJob(&(curJob), "item destroyed or missing");
				return;
			}
			RequestQueues::entityRequests.push_back(entRequest::delEntRequest(curJob.targetEnt->uid, ENT_TYPE_ITEM));
			curMap->setTasked(curJob.targetPoint->tileX, curJob.targetPoint->tileY, false);
			curMap->setColor(curJob.targetPoint->tileX, curJob.targetPoint->tileY, COLOR_NONE);
			curMap->setRoom(curJob.targetPoint->tileX, curJob.targetPoint->tileY, curJob.roomIDToBuild);
			// DEBUG:
			curMap->setTile(curJob.targetPoint->tileX, curJob.targetPoint->tileY, 0);
			break;
		}
	}
}

// Like so many other things, this has become a mess
void AI::progressJobStage() {
	switch(jobState) {
		case JOB_STAGE_WALKING_TO_DEST: {
			switch(curJob.type) {
				case JOB_TYPE_BUILD: {
					if (curJob.targetEnt == NULL) {
						cancelJob(&(curJob), "item destroyed or missing");
					}

					Item* targetItem = ((Item*) curJob.targetEnt);
					if (controlled->hasItem(targetItem)) {
						float dx = curJob.targetPoint->realX - controlled->realX;
						float dy = curJob.targetPoint->realY - controlled->realY;
						if (dx*dx + dy*dy > UNIT_PICKUP_DISTANCE) {
							walkToPoint(curJob.targetPoint);
						} else {
							// Job success
							jobState = JOB_STAGE_ACTING;
							controlled->startTask(0.5);
						}
					} else if (targetItem->inInventory) {
						cancelJob(&(curJob), "item destroyed or missing");
					} else {
						float dx = curJob.targetEnt->realX - controlled->realX;
						float dy = curJob.targetEnt->realY - controlled->realY;
						if (dx*dx + dy*dy > UNIT_PICKUP_DISTANCE) {
							point* targetPoint = Map::TexXYToTileXY(curJob.targetEnt->realX, curJob.targetEnt->realY);
							walkToPoint(targetPoint);
						} else {
							Item* targetItem = (Item*)curJob.targetEnt;
							controlled->pickupItem(targetItem);
						}
					}
					break;
				}
				case JOB_TYPE_MINING:
				case JOB_TYPE_WOODCUT: {
					jobState = JOB_STAGE_ACTING;
					controlled->startTask(0.5);
					break;
				}
			}
			break;
		}
		case JOB_STAGE_ACTING: {
			finishJob();
			break;
		}
		default:
		break;
	}
}

// Dunno how much (if at all) I want to subclass AI, so it is non-virtual for now
void AI::update(float dt) {
	if (controlled->state == STATE_WALKING) {
		continueWalking();
	} else if (controlled->state == STATE_FINISHED_JOB) {
		progressJobStage();
	} else {
		timeSinceLastUpdate -= dt;
		if (timeSinceLastUpdate <= 0) {
			if (controlled->state == STATE_IDLE) {
				if (!checkJobBoard()) {
					timeSinceLastUpdate = UNIT_AI_UPDATE_TIME;
				}
			}
		}
	}
}