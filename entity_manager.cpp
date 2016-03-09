#include "entity_manager.hpp"

void EntityManager::render(sf::RenderTarget* screen) {
	unitManager->render(screen);
	doodadManager->render(screen);
}

void EntityManager::flushRequests() {
	while (!RequestQueues::entityRequests.empty()) {
		// parse this request
		entRequest request = RequestQueues::entityRequests.back();
		if (request.entType == ENT_TYPE_UNIT) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				Unit* newUnit = unitManager->addNewUnitByType(request.entName);
				newUnit->moveToRealXY( 	request.X,
										request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				unitManager->removeUnit(request.uid);
			} else {
				std::cerr << "Unknown request found of type " << request.entRequestType << " for unit manager." << std::endl;
			}
		} else if (request.entType == ENT_TYPE_DOODAD) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				Doodad* newDoodad = doodadManager->addDoodadByType(request.entName);
				newDoodad->moveToRealXY( request.X,
										 request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				doodadManager->removeDoodad(request.uid);
			} else {
				std::cerr << "Unknown request found of type " << request.entRequestType << " for doodad manager." << std::endl;
			}
		} else {
			std::cerr << "Unknown request found of type " << request.entRequestType << " and ent type " << request.entType << std::endl;
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