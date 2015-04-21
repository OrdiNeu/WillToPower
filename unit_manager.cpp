#include "unit_manager.hpp"

std::vector<Unit*> UnitManager::units;

void UnitManager::render(sf::RenderTarget* screen) {
	for (Unit* thisUnit : units) {
		thisUnit->render(screen);
	}
}

void UnitManager::update(float dt) {
	for (Unit* thisUnit : units) {
		thisUnit->update(dt);

		// Handle kinesthetics
		thisUnit->realX += thisUnit->dx;
		thisUnit->realY += thisUnit->dy;

		// Tell the AI to move to the next location, if necessary
		// TODO: Move this to an AI class for each unit
		if (thisUnit->state == STATE_WALKING) {
			point* thisPoint = Map::TexXYToTileXY(thisUnit->realX, thisUnit->realY);
			if (thisPoint->tileX != thisUnit->tileX || thisPoint->tileY != thisUnit->tileY) {
				std::cout << "Unit has moved" << std::endl;
				// Are we at the target location?
				point* nextLoc = thisUnit->curPath.back();
				if (thisPoint->tileX != nextLoc->tileX || thisPoint->tileY != nextLoc->tileY) {
					std::cout << "Unit ended up somewhere unexpected - need to recreate path" << std::endl;
					std::cout << "(Expected " << nextLoc->tileX << "," << nextLoc->tileY << "), got (" << thisPoint->tileX << "," << thisPoint->tileY << "))" << std::endl;
					// We meed to recreate the path
					int targetX, targetY;
					while (!thisUnit->curPath.empty()) {
						point* pathPoint = thisUnit->curPath.back();
						targetX = pathPoint->tileX;
						targetY = pathPoint->tileY;
						thisUnit->curPath.pop_back();
						delete pathPoint;
					}
					thisUnit->curPath = AStarSearch(curMap, thisPoint->tileX, thisPoint->tileY, targetX, targetY);
					// Remove the last point in the route, since it is the current position
					/*point* last_point = thisUnit->curPath.back();
					delete last_point;
					thisUnit->curPath.pop_back();*/
				} else {
					// Just remove this point from the unit's list - it'll take care of the rest
					point* pathPoint = thisUnit->curPath.back();
					thisUnit->curPath.pop_back();
					thisUnit->tileX = thisPoint->tileX;
					thisUnit->tileY = thisPoint->tileY;
					delete pathPoint;
				}
			}
			delete thisPoint;
		}
	}
}

void UnitManager::addUnit(Unit* unit){
	UnitManager::units.push_back(unit);
}