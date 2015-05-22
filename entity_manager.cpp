#include "entity_manager.hpp"

void EntityManager::render(sf::RenderTarget* screen) {
	unitManager->render(screen);
	doodadManager->render(screen);
}

void EntityManager::update(float dt) {
	unitManager->update(dt);
	doodadManager->update(dt);

	// Handle entity requests
	for (std::string request : RequestQueues::entityRequests) {
		// regex parse this
	}
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
void EntityManager::removeEnt(std::string id, int type) {
	if (type & ENTITY_UNIT) {
		unitManager->removeUnit(id);
	} else if (type & ENTITY_DOODAD) {
		doodadManager->removeDoodad(id);
	}
};