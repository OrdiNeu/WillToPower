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

void DoodadManager::addNewDoodadType(std::string type, Doodad newDoodad) {
	doodad_library[type] = newDoodad;
}

Doodad* DoodadManager::addDoodadByType(std::string type) {
	// Ensure that the type exists
	if (doodad_library.find(type) == doodad_library.end()) {
		std::cerr << "ERROR: attempted to create doodad of unknown type " << type << std::endl;
		return NULL;
	}
	std::ostringstream stream;
	stream << type << "_" << num_units_created[type]++;
	Doodad* newDoodad = doodad_library[type].clone(stream.str());
	addDoodad(newDoodad);
	return newDoodad;
}

void DoodadManager::removeDoodad(std::string uid) {
	// Find the Doodad and do an in-place swap with the final element, then shrink
	for (std::vector<Doodad*>::iterator it = doodads.begin() ; it != doodads.end(); ++it) {
		if ((*it)->uid == uid) {
			*it = doodads[doodads.size()-1];
			doodads.pop_back();
			break;
		}
	}
}

std::vector<Doodad*> DoodadManager::getDoodadsAtPoint(int x, int y) {
	std::vector<Doodad*> retVal;
	for(Doodad* thisDoodad : doodads) {
		// slow af
		point* doodadPos = Map::TexXYToTileXY(thisDoodad->realX, thisDoodad->realY);
		if (doodadPos->tileX == x && doodadPos->tileY == y) {
			retVal.push_back(thisDoodad);
		}
		delete doodadPos;
	}
	return retVal;
}