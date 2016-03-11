#include "entity_manager.hpp"

void EntityManager::render(sf::RenderTarget* screen) {
	// Single run of a bubble sort while we go through the array
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
	// Needs a refactor
	while (!RequestQueues::entityRequests.empty()) {
		bool error = false;
		// parse this request
		entRequest request = RequestQueues::entityRequests.back();
		Entity* newEnt;
		if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
			newEnt = addNewEntByType(request.entName, request.entType);
			if (newEnt) {
				ents.push_back(newEnt);
				newEnt->moveToRealXY( 	request.X,
										request.Y);
				std::cout << newEnt->uid << " Added OK" << std::endl;
			}
		} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
			removeEnt(request.uid, request.entType);
			/*for (std::vector<Entity*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
				if ((*it)->uid == request.uid) {
					*it = ents[ents.size()-1];
					ents.pop_back();
					std::cout << "Removed OK" << std::endl;
				}
			}*/
			for (typename std::vector<Entity*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
				if ((*it)->uid == request.uid) {
					*it = ents[ents.size()-1];
					ents.pop_back();
					std::cout << "Removed OK" << std::endl;
				}
			}
		} else {
			error = true;
		}
		/*if (request.entType == ENT_TYPE_UNIT) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				newEnt = unitManager->addNewEntByType(request.entName);
				newEnt->moveToRealXY( 	request.X,
										request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				unitManager->removeEnt(request.uid);
			} else {
				error = true;
			}
		} else if (request.entType == ENT_TYPE_DOODAD) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				newEnt = doodadManager->addNewEntByType(request.entName);
				newEnt->moveToRealXY( request.X,
										 request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				doodadManager->removeEnt(request.uid);
			} else {
				error = true;
			}
		} else if (request.entType == ENT_TYPE_ITEM) {
			if (request.entRequestType == ENT_REQUEST_NEW_ENT) {
				newEnt = itemManager->addNewEntByType(request.entName);
				newEnt->moveToRealXY(	request.X,
										request.Y);
			} else if (request.entRequestType == ENT_REQUEST_DEL_ENT) {
				itemManager->removeEnt(request.uid);
			} else {
				error = true;
			}
		} else {
			error = true;
		}*/

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

Entity* EntityManager::addNewEntByType(std::string name, int type) {
	if (type == ENT_TYPE_UNIT) {
		return unitManager->addNewEntByType(name);
	} else if (type == ENT_TYPE_DOODAD) {
		return doodadManager->addNewEntByType(name);
	} else if (type == ENT_TYPE_ITEM) {
		return itemManager->addNewEntByType(name);
	} else {
		std::cerr << "addNewEntByType called on unknown entity" << std::endl;
	}
	return NULL;
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
	}
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
};