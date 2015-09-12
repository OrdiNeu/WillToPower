#include "unit_ai.hpp"
using namespace std;

AI::AI(Unit* controlled, Map* curMap) : controlled(controlled), curMap(curMap) {
	timeSinceLastUpdate = UNIT_AI_UPDATE_TIME;
}

// Dunno how much (if at all) I want to subclass AI, so it is non-virtual for now
void AI::update(float dt) {
	if (controlled->state == STATE_WALKING) {
		point* thisPoint = Map::TexXYToTileXY(controlled->realX, controlled->realY);
		if (thisPoint->tileX != controlled->tileX || thisPoint->tileY != controlled->tileY) {
			// See if we've sufficiently close to the center of the tile
#ifdef AI_MOVE_CENTER_OF_TILE
			point* centerPoint = Map::TileXYToTexXY(thisPoint->tileX, thisPoint->tileY);
			float dx = controlled->realX - centerPoint->realX;
			float dy = controlled->realY - centerPoint->realY;
			if (dx * dx + dy * dy < DISTANCE_FROM_CENTER_SQ) {
#endif
				// Are we at the target location?
				point* nextLoc = controlled->curPath.back();
				if (thisPoint->tileX != nextLoc->tileX || thisPoint->tileY != nextLoc->tileY) {
					std::cout << "Unit ended up somewhere unexpected - need to recreate path" << std::endl;
					std::cout << "(Expected " << nextLoc->tileX << "," << nextLoc->tileY << "), got (" << thisPoint->tileX << "," << thisPoint->tileY << "))" << std::endl;
					// We meed to recreate the path
					int targetX, targetY;
					while (!controlled->curPath.empty()) {
						point* pathPoint = controlled->curPath.back();
						targetX = pathPoint->tileX;
						targetY = pathPoint->tileY;
						controlled->curPath.pop_back();
						delete pathPoint;
					}
					controlled->curPath = AStarSearch(curMap, thisPoint->tileX, thisPoint->tileY, targetX, targetY);
					// Remove the last point in the route, since it is the current position
					point* last_point = controlled->curPath.back();
					delete last_point;
					controlled->curPath.pop_back();
				} else {
					// Just remove this point from the unit's list - it'll take care of the rest
					point* pathPoint = controlled->curPath.back();
					controlled->curPath.pop_back();
					controlled->tileX = thisPoint->tileX;
					controlled->tileY = thisPoint->tileY;
					delete pathPoint;
				}
#ifdef AI_MOVE_CENTER_OF_TILE
			}
#endif
		}
		delete thisPoint;
	} else {
		timeSinceLastUpdate -= dt;
		if (timeSinceLastUpdate <= 0) {
			timeSinceLastUpdate = UNIT_AI_UPDATE_TIME;

			// Check the job board for stuff to do
			int jobPicked = -1;
			for (unsigned int i = 0; i < JobQueue::jobQueue.size(); i++) {
				Job job = JobQueue::jobQueue[i];
				if (!job.suspended) {
					if (job.targetEnt == controlled || job.targetEnt == NULL) {
						if ((job.requirements & controlled->skills) == job.requirements) {
							// Try to pick this job up
							std::vector<point*> route = AStarSearch(curMap, controlled->tileX, controlled->tileY, job.targetPoint->tileX, job.targetPoint->tileY);
							if (route.size() != 0) {
								// Remove the last point in the route, since it is the current position
								point* last_point = route.back();
								delete last_point;
								route.pop_back();

								// Walk to the target location
								controlled->walkTo(route);
								jobPicked = i;
								break;
							}
						}
					}
				}
			}

			// Is there a job that is now taken?
			if (jobPicked >= 0) {
				JobQueue::jobQueue.erase(JobQueue::jobQueue.begin() + jobPicked);
			}
		}
	}
}