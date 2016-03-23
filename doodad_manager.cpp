#include "doodad_manager.hpp"

std::vector<Doodad*> DoodadManager::getDoodadsAtPoint(int x, int y) {
	std::vector<Doodad*> retVal;
	for(Doodad* thisDoodad : ents) {
		// slow af
		point doodadPos = TexXYToTileXY(thisDoodad->realX, thisDoodad->realY);
		if (doodadPos.tileX == x && doodadPos.tileY == y) {
			retVal.push_back(thisDoodad);
		}
	}
	return retVal;
}

void DoodadManager::addEnt(Doodad* ent){
	point entPos = TexXYToTileXY(ent->realX, ent->realY);
	ents.push_back(ent);
	if (ent->hasTags(PATHING_BLOCK)) {
		curMap->setWalkableStatus(entPos.tileX, entPos.tileY, false);
	}
}

Doodad* DoodadManager::removeEnt(std::string uid) {
	// Find the entity and do an in-place swap with the final element, then shrink
	for (typename std::vector<Doodad*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
		if ((*it)->uid == uid) {
			Doodad* removedEnt = *it;
			*it = ents[ents.size()-1];
			ents.pop_back();
			if (removedEnt->hasTags(PATHING_BLOCK)) {
				point entPos = TexXYToTileXY(removedEnt->realX, removedEnt->realY);
				curMap->resetWalkableStatus(entPos.tileX, entPos.tileY);
			};
			return removedEnt;
		}
	}
	return NULL;
};