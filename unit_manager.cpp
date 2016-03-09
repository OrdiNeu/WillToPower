#include "unit_manager.hpp"

void UnitManager::render(sf::RenderTarget* screen) {
	for (Unit* thisUnit : units) {
		thisUnit->render(screen);
	}
}

void UnitManager::update(float dt) {
	for (Unit* thisUnit : units) {
		thisUnit->update(dt);

		// Handle kinesthetics
		float new_x = thisUnit->realX + thisUnit->dx;
		float new_y = thisUnit->realY + thisUnit->dy;
		point* new_point = Map::TexXYToTileXY(new_x, new_y);
		if (curMap->isWalkable(new_point->tileX,new_point->tileY)) {
			thisUnit->realX += thisUnit->dx;
			thisUnit->realY += thisUnit->dy;
		}
		delete new_point;
	}

	for (AI* thisAI : ais) {
		thisAI->update(dt);
	}
}

Unit* UnitManager::addNewUnitByType(std::string type) {
	// Ensure that the type exists
	if (unit_library.find(type) == unit_library.end()) {
		std::cerr << "ERROR: attempted to create unit of unknown type " << type << std::endl;
		return NULL;
	}
	// Construct a name for the unit
	std::ostringstream stream;
	stream << type << "_" << num_units_created[type]++;

	Unit* newUnit = unit_library[type].clone(stream.str());	// TODO: Lookup how to convert integers to string
	AI* newAI = new AI(newUnit, curMap);
	addUnit(newAI);
	lastCreatedUnit = newUnit;
	return newUnit;
}

void UnitManager::addNewUnitType(std::string type, Unit newUnit) {
	unit_library[type] = newUnit;
}

void UnitManager::addUnit(AI* ai) {
	ais.push_back(ai);
	units.push_back(ai->controlled);
}

void UnitManager::removeUnit(std::string uid) {
	// Find the AI and do an in-place swap with the final element, then shrink
	for (std::vector<AI*>::iterator it = ais.begin() ; it != ais.end(); ++it) {
		if ((*it)->uid == uid) {
			*it = ais[ais.size()-1];
			ais.pop_back();
		}
	}

	// Do the same for the connected unit
	for (std::vector<Unit*>::iterator it = units.begin() ; it != units.end(); ++it) {
		if ((*it)->uid == uid) {
			*it = units[units.size()-1];
			units.pop_back();
		}
	}
}