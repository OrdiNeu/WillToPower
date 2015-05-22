#include "doodad_manager.hpp"

void DoodadManager::render(sf::RenderTarget* screen) {
	for (Doodad* thisDoodad : doodads) {
		thisDoodad->render(screen);
	}
}

void DoodadManager::update(float dt) {
	for (Doodad* thisDoodad : doodads) {
		thisDoodad->update(dt);
	}
}

void DoodadManager::addDoodad(Doodad* doodad) {
	doodads.push_back(doodad);
}

void DoodadManager::removeDoodad(std::string id) {
	// Find the Doodad and do an in-place swap with the final element, then shrink
	for (std::vector<Doodad*>::iterator it = doodads.begin() ; it != doodads.end(); ++it) {
		if ((*it)->id == id) {
			*it = doodads[doodads.size()-1];
			doodads.pop_back();
		}
	}
}