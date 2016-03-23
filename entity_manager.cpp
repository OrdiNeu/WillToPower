#include "entity_manager.hpp"

void EntityManager::render(sf::RenderTarget* screen) {
	// Single run of a bubble sort while we go through and render
	for (std::vector<Entity*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
		Entity* ent = *it;
		Entity* nextEnt = *(it+1);
		if ((it+1) != ents.end() && ent->realY > nextEnt->realY) {
			*it = (*(it+1));
			(*(it+1)) = ent;
			ent = nextEnt;
		}
		ent->render(screen);
	}
}

void EntityManager::flushRequests() {
	while (!RequestQueues::entityRequests.empty()) {
		// parse this request
		entRequest request = RequestQueues::entityRequests.back();
		if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
			addNewEntByType(request.entName, request.entType, request.X, request.Y);
		} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
			removeEnt(request.uid, request.entType);
		} else {
			std::cerr << "Unknown request found of type " << request.entRequestType << " and ent type " << request.entType << std::endl;
		}

 		RequestQueues::entityRequests.pop_back();
	}
}

void EntityManager::update(float dt) {
	unitManager->update(dt);
	doodadManager->update(dt);
	itemManager->update(dt);

	flushRequests();
}

void EntityManager::addToEntList(Entity* newEnt) {
	bool entered = false;
	for (typename std::vector<Entity*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
		if ((*it)->realY >= newEnt->realY) {
			ents.insert(it, newEnt);
			entered = true;
			break;
		}
	}

	if (!entered) {
		ents.push_back(newEnt);
	}
}

Entity* EntityManager::addNewEntByType(std::string name, int type, float x, float y) {
	Entity* newEnt;
	if (type == ENT_TYPE_UNIT) {
		newEnt = unitManager->addNewEntByType(name, x, y);
	} else if (type == ENT_TYPE_DOODAD) {
		newEnt = doodadManager->addNewEntByType(name, x, y);
	} else if (type == ENT_TYPE_ITEM) {
		newEnt = itemManager->addNewEntByType(name, x, y);
	}

	if (newEnt != NULL) {
		addToEntList(newEnt);
	}
	return newEnt;
};

void EntityManager::addEnt(Entity* ent, int type) {
	if (type == ENT_TYPE_UNIT) {
		unitManager->addEnt((AI*) ent);
	} else if (type == ENT_TYPE_DOODAD) {
		doodadManager->addEnt((Doodad*) ent);
	} else if (type == ENT_TYPE_ITEM) {
		itemManager->addEnt((Item*) ent);
	} else {
		std::cerr << "addEnt called on unknown entity" << std::endl;
		return;
	}
	addToEntList(ent);
};

// The in-place swap children do may mess up for loops that are iterating over ents
// But then, there are always problems with removals during iteration
void EntityManager::removeEnt(std::string uid, int type) {
	if (type == ENT_TYPE_UNIT) {
		unitManager->removeEnt(uid);
	} else if (type == ENT_TYPE_DOODAD) {
		doodadManager->removeEnt(uid);
	} else if (type == ENT_TYPE_ITEM) {
		itemManager->removeEnt(uid);
	} else {
		std::cerr << "removeEnt called on unknown entity" << std::endl;
	}

	for (typename std::vector<Entity*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
		if ((*it)->uid == uid) {
			delete *it;
			*it = ents[ents.size()-1];
			ents.pop_back();
		}
	}
};