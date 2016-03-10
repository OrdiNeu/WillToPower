#include "entity_manager.hpp"

void EntityManager::render(sf::RenderTarget* screen) {
	unitManager->render(screen);
	doodadManager->render(screen);
	itemManager->render(screen);
}

void EntityManager::flushRequests() {
	// Needs a refactor
	while (!RequestQueues::entityRequests.empty()) {
		bool error = false;
		// parse this request
		entRequest request = RequestQueues::entityRequests.back();
		if (request.entType == ENT_TYPE_UNIT) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				Unit* newUnit = unitManager->addNewEntByType(request.entName);
				newUnit->moveToRealXY( 	request.X,
										request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				unitManager->removeEnt(request.uid);
			} else {
				error = true;
			}
		} else if (request.entType == ENT_TYPE_DOODAD) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				Doodad* newDoodad = doodadManager->addNewEntByType(request.entName);
				newDoodad->moveToRealXY( request.X,
										 request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				doodadManager->removeEnt(request.uid);
			} else {
				error = true;
			}
		} else if (request.entType == ENT_TYPE_ITEM) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				Item* newItem = itemManager->addNewEntByType(request.entName);
				newItem->moveToRealXY(	request.X,
										request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				itemManager->removeEnt(request.uid);
			} else {
				error = true;
			}
		} else {
			error = true;
		}
		if (error) {
			std::cerr << "Unknown request found of type " << request.entRequestType << " and ent type " << request.entType << std::endl;
		}
 		RequestQueues::entityRequests.pop_back();
	}
}

void EntityManager::update(float dt) {
	unitManager->update(dt);
	doodadManager->update(dt);
	itemManager->update(dt);

	// Handle entity requests
	flushRequests();
}

void EntityManager::addEnt(Entity* ent, int type) {
	if (type & ENTITY_UNIT) {
		unitManager->addEnt((AI*) ent);
	} else if (type & ENTITY_DOODAD) {
		doodadManager->addEnt((Doodad*) ent);
	} else if (type & ENTITY_ITEM) {
		itemManager->addEnt((Item*) ent);
	} else {
		std::cerr << "addEnt called on unknown entity" << std::endl;
	}
};

// The in-place swap children do may mess up for loops that are iterating over ents
// But then, there are always problems with removals during iteration
void EntityManager::removeEnt(std::string uid, int type) {
	if (type & ENTITY_UNIT) {
		unitManager->removeEnt(uid);
	} else if (type & ENTITY_DOODAD) {
		doodadManager->removeEnt(uid);
	} else if (type & ENTITY_ITEM) {
		itemManager->removeEnt(uid);
	} else {
		std::cerr << "removeEnt called on unknown entity" << std::endl;
	}
};