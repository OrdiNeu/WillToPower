#include "entity_manager.hpp"

void EntityManager::render(sf::RenderTarget* screen) {
	unitManager->render(screen);
	doodadManager->render(screen);
}

void EntityManager::flushRequests() {
	while (!RequestQueues::entityRequests.empty()) {
		// parse this request
		entRequest request = RequestQueues::entityRequests.back();
		if (request.entRequestType == ENT_REQUEST_NEW_UNIT) {
			Unit* newUnit = unitManager->addNewUnitByType(request.unitName);
			newUnit->moveToRealXY( 	request.X,
									request.Y);
			//std::cout << "Adding ent to " << request.X << ", " << request.Y;
		} else if (request.entRequestType == ENT_REQUEST_DEL_UNIT) {
			//Doodad* newDoodad = doodadManager->addDoodadByType();
			//newDoodad.pos = asjdfhakf
		}
		RequestQueues::entityRequests.pop_back();
	}
}

void EntityManager::update(float dt) {
	unitManager->update(dt);
	doodadManager->update(dt);

	// Handle entity requests
	flushRequests();
}

void EntityManager::addEnt(Entity* ent, int type) {
	if (type & ENTITY_UNIT) {
		unitManager->addUnit((AI*) ent);
	} else if (type & ENTITY_DOODAD) {
		doodadManager->addDoodad((Doodad*) ent);
	}
};

// The in-place swap childrens do may mess up for loops that are iterating over ents
// But then, there are always problems with removals during iteration
void EntityManager::removeEnt(std::string uid, int type) {
	if (type & ENTITY_UNIT) {
		unitManager->removeUnit(uid);
	} else if (type & ENTITY_DOODAD) {
		doodadManager->removeDoodad(uid);
	}
};