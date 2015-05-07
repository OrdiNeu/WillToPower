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
		thisUnit->realX += thisUnit->dx;
		thisUnit->realY += thisUnit->dy;
	}

	for (AI* thisAI : ais) {
		thisAI->update(dt);
	}
}

void UnitManager::addUnit(AI* ai) {
	ais.push_back(ai);
	units.push_back(ai->controlled);
}

void UnitManager::removeUnit(std::string id) {
	// Find the AI and do an in-place swap with the final element, then shrink
	for (std::vector<AI*>::iterator it = ais.begin() ; it != ais.end(); ++it) {
		if ((*it)->id == id) {
			*it = ais[ais.size()-1];
			ais.pop_back();
		}
	}

	// Do the same for the connected unit
	for (std::vector<Unit*>::iterator it = units.begin() ; it != units.end(); ++it) {
		if ((*it)->id == id) {
			*it = units[units.size()-1];
			units.pop_back();
		}
	}
}