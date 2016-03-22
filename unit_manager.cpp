#include "unit_manager.hpp"

void UnitManager::update(float dt) {
	for (Unit* thisUnit : ents) {
		thisUnit->update(dt);

		// Handle kinesthetics
		float new_x = thisUnit->realX + thisUnit->dx;
		float new_y = thisUnit->realY + thisUnit->dy;
		point new_point = Map::TexXYToTileXY(new_x, new_y);
		if (curMap->isWalkable(new_point.tileX,new_point.tileY)) {
			thisUnit->realX += thisUnit->dx;
			thisUnit->realY += thisUnit->dy;
		}
	}

	for (AI* thisAI : ais) {
		thisAI->update(dt);
	}
}

Unit* UnitManager::addNewEntByType(std::string type) {
	// Ensure that the type exists
	if (ent_library.find(type) == ent_library.end()) {
		std::cerr << "ERROR: attempted to create unit of unknown type " << type << std::endl;
		return NULL;
	}
	
	// Construct a name for the unit
	std::ostringstream stream;
	stream << type << "_" << num_ents_created[type]++;

	Unit* newUnit = ent_library[type].clone(stream.str());
	AI* newAI = new AI(newUnit, curMap);
	addEnt(newAI);
	lastCreatedEnt = newUnit;
	return newUnit;
}

void UnitManager::addEnt(AI* ai) {
	ais.push_back(ai);
	ents.push_back(ai->controlled);
}

Unit* UnitManager::removeEnt(std::string uid) {
	// Find the AI and do an in-place swap with the final element, then shrink
	for (std::vector<AI*>::iterator it = ais.begin() ; it != ais.end(); ++it) {
		if ((*it)->uid == uid) {
			*it = ais[ais.size()-1];
			ais.pop_back();
		}
	}

	// Do the same for the connected unit
	for (std::vector<Unit*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
		if ((*it)->uid == uid) {
			Unit* deletedUnit = *it;
			*it = ents[ents.size()-1];
			ents.pop_back();
			return deletedUnit;
		}
	}
	
	return NULL;
}