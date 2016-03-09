#include "doodad_manager.hpp"

std::vector<Doodad*> DoodadManager::getDoodadsAtPoint(int x, int y) {
	std::vector<Doodad*> retVal;
	for(Doodad* thisDoodad : ents) {
		// slow af
		point* doodadPos = Map::TexXYToTileXY(thisDoodad->realX, thisDoodad->realY);
		if (doodadPos->tileX == x && doodadPos->tileY == y) {
			retVal.push_back(thisDoodad);
		}
		delete doodadPos;
	}
	return retVal;
}