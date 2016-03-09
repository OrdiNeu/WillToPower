#include "world_generator.hpp"

const float PerlinScalingFactor1 = 20.0;
const float PerlinScalingFactor2 = 8.0;
const float PerlinScalingFactor3 = 3.0;
const float PerlinWeightFactor1 = 2;
const float PerlinWeightFactor2 = 2;
const float PerlinWeightFactor3 = 2;

WorldGenerator::WorldGenerator(int seed, EntityManager* entManager) : seed(seed), entManager(entManager) {
	srand(seed);
	createGenerators();
}

WorldGenerator::WorldGenerator(EntityManager* entManager) : entManager(entManager) {
	createGenerators();
}

void WorldGenerator::createGenerators() {
	forestryGen1 = new PerlinNoiseGenerator(rand());
	forestryGen2 = new PerlinNoiseGenerator(rand());
	forestryGen3 = new PerlinNoiseGenerator(rand());
}

void WorldGenerator::addDefaultTiles(Map* map) {
	Tile* emptyTile = new Tile();
	map->addTile(emptyTile);
	Tile* grassTile = new Tile("./data/images/GrassTile1.png", IS_WALKABLE);
	map->addTile(grassTile);
	Tile* dirtTile = new Tile("./data/images/DirtTile1.png", IS_WALKABLE);
	map->addTile(dirtTile);
	Tile* dirtTile2 = new Tile("./data/images/DirtTile2.png", IS_WALKABLE);
	map->addTile(dirtTile2);
	Tile* dirtBlock = new Tile("./data/images/DirtBlock1.png", IS_MINABLE | WALL);
	map->addTile(dirtBlock);
	Doodad tree = Doodad("TREE", "./data/images/Tree.png", 0, 0, IS_TREE);
	entManager->doodadManager->addNewEntType("Tree", tree);
}

Map* WorldGenerator::generateMap(int map_x, int map_y) {
	Map* retVal = new Map();
	retVal->init(MAP_WIDTH, MAP_HEIGHT);
	
	addDefaultTiles(retVal);

	// Get the forest layer
	for (int x = 0; x < retVal->width; x++) {
		for (int y = 0; y < retVal->height; y++) {
			double forestFactor = forestryGen3->get(float(x)/PerlinScalingFactor3, float(y)/PerlinScalingFactor3)*PerlinWeightFactor3;
			forestFactor +=  forestryGen2->get(float(x)/PerlinScalingFactor2, float(y)/PerlinScalingFactor2)*PerlinWeightFactor2;
			forestFactor +=  forestryGen1->get(float(x)/PerlinScalingFactor1, float(y)/PerlinScalingFactor1)*PerlinWeightFactor1;
			if (forestFactor > 0) {
				// This is a forest-y region
				retVal->setTile(x,y,1);
				// If the 6th digit is a 2, 1, or 0, put a tree here
				if (rand() % 10 < 3) {
					//Doodad* thisTree = entManager->doodadManager->addDoodadByType("Tree");
					point* thisPoint = Map::TileXYToTexXY(x,y);
					//thisTree->moveToRealXY(thisPoint->realX,thisPoint->realY);
					RequestQueues::entityRequests.push_back(entRequest::newEntRequest("Tree", thisPoint->realX, thisPoint->realY, ENT_TYPE_DOODAD));
					delete thisPoint;
				}
			} else if (forestFactor < -0.5) {
				// This is a dry region
				if (rand() % 2 == 1) {
					retVal->setTile(x,y,2);
				} else {
					retVal->setTile(x,y,4);
				}
			}
		}
	}
	return retVal;
}