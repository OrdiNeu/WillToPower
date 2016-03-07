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

// Cause the controlled unit to move to the next point on its list
void AI::moveToNextPoint() {
	point* last_point = controlled->curPath.back();
	delete last_point;
	controlled->curPath.pop_back();
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
	if ((job.requirements & controlled->skills) == 0) {
		return false;
	}

	return true;
}

bool AI::pickUpJob() {
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
		switch(job.type) {
			case JOB_TYPE_MINING: {
				if (job.targetPoint == NULL) {
					std::cerr << "Error: mining job created without a target point" << std::endl;
				} else {
					std::vector<point*> route = AStarSearch(curMap, curPoint->tileX, curPoint->tileY, job.targetPoint->tileX, job.targetPoint->tileY);
					if (route.size() != 0) {
						// Remove the last point in the route, since it is the current position
						point* last_point = route.back();
						delete last_point;
						route.pop_back();

						// Walk to the target location
						controlled->walkTo(route);

						// Pick up the job
						jobPicked = i;
						job.assigned = controlled;
						jobState = JOB_STAGE_WALKING_TO_DEST;
						delete curPoint;
					} else {
						std::cout << "Job suspended: Could not reach target." << std::endl;
						JobQueue::jobQueue[i].suspended = true;
					}
				}
				break;
			}
			case JOB_TYPE_WOODCUT: {
				if (job.targetEnt == NULL) {
					std::cerr << "Error: woodcut job created without a target ent" << std::endl;
					point* targetPoint = Map::TexXYToTileXY(job.targetEnt->realX, job.targetEnt->realY);
					route = AStarSearch(curMap, curPoint->tileX, curPoint->tileY, targetPoint->tileX, targetPoint->tileY);
					delete targetPoint;
				}
			}
		}
		delete curPoint;
		// Is there a job that is now taken?
		if (jobPicked >= 0) {
			curJob = job;
			JobQueue::jobQueue.erase(JobQueue::jobQueue.begin() + jobPicked);
			return true;
		}
	}
	return false;
}

// Dunno how much (if at all) I want to subclass AI, so it is non-virtual for now
void AI::update(float dt) {
	if (controlled->state == STATE_WALKING) {
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
	} else if (controlled->state == STATE_FINISHED_JOB) {
		switch(jobState) {
			case JOB_STAGE_WALKING_TO_DEST: {
				jobState = JOB_STAGE_ACTING;
				controlled->state = STATE_FINISHED_JOB;
				break;
			}
			case JOB_STAGE_ACTING: {
				jobState = 0;
				controlled->state = STATE_IDLE;
				if (curJob.targetPoint != NULL) {
					curMap->setTasked(curJob.targetPoint->tileX,curJob.targetPoint->tileY, false);
					curMap->setColor(curJob.targetPoint->tileX,curJob.targetPoint->tileY, COLOR_NONE);
				}
				break;
			}
			default:
			break;
		}
	} else {
		timeSinceLastUpdate -= dt;
		if (timeSinceLastUpdate <= 0) {
			if (!pickUpJob()) {
				timeSinceLastUpdate = UNIT_AI_UPDATE_TIME;
			}
		}
	}
}