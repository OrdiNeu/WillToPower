#include "entity_manager.hpp"

void EntityManager::render(sf::RenderTarget* screen) {
	unitManager->render(screen);
	doodadManager->render(screen);
}

void EntityManager::update(float dt) {
	unitManager->update(dt);
	doodadManager->update(dt);

	// Handle entity requests
	/*std::string teststr("Test0");
	std::regex test("Test(.+)");
	std::regex_match(teststr, group, test);
	for (unsigned i=0; i<group.size(); ++i) {
	  std::cout << "[" << group[i] << "] ";
	}
	std::cout << std::endl;*/

	std::smatch group;
	std::regex add_unit("NEW_UNIT:(?:.*):(.*):(.*)");	// ADD_UNIT:typeID:X:Y
	std::regex add_doodad("NEW_DOODAD:(.*):(.+):(.+)");	// ADD_DOODAD:typeID:X:Y
	while (!RequestQueues::entityRequests.empty()) {
		// regex parse this
		std::string request = RequestQueues::entityRequests.back();
		std::cout << "Got request " << request << std::endl;
		if (std::regex_match(request, group, add_unit)) {
			for (unsigned i=0; i<group.size(); ++i) {
			  std::cout << "[" << group[i] << "] ";
			}
			std::string X = group.str(2).c_str()+1;
			std::string Y = group.str(2).c_str()+1;
			Unit* newUnit = unitManager->addNewUnitByType(group[1]);
			newUnit->moveToRealXY( 	atoi(X),
									atoi(Y));
			std::cout << "Adding ent to " << X << ", " << Y;
		} else if (std::regex_match(request, group, add_doodad)) {
			//Doodad* newDoodad = doodadManager->addDoodadByType();
			//newDoodad.pos = asjdfhakf
		}
		RequestQueues::entityRequests.pop_back();
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