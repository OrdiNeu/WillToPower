#include "unit_manager.hpp"

std::vector<Unit*> UnitManager::units;
std::vector<AI*> UnitManager::ais;

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

void UnitManager::addUnit(AI* ai){
	ais.push_back(ai);
	units.push_back(ai->controlled);
}