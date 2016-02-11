#include "world_generator.hpp"

const float PerlinScalingFactor1 = 20.0;
const float PerlinScalingFactor2 = 8.0;
const float PerlinScalingFactor3 = 3.0;
const float PerlinWeightFactor1 = 2;
const float PerlinWeightFactor2 = 1.5;
const float PerlinWeightFactor3 = 1;

WorldGenerator::WorldGenerator(int seed, EntityManager* entManager) : seed(seed), entManager(entManager) {
	srand(seed);
	//TODO: Read up on "shadowing a parameter" so I can just call the other version below
	forestryGen1 = new PerlinNoiseGenerator(rand());
	forestryGen2 = new PerlinNoiseGenerator(rand());
	forestryGen3 = new PerlinNoiseGenerator(rand());
}

WorldGenerator::WorldGenerator(EntityManager* entManager) : entManager(entManager) {
	forestryGen1 = new PerlinNoiseGenerator(rand());
	forestryGen2 = new PerlinNoiseGenerator(rand());
	forestryGen3 = new PerlinNoiseGenerator(rand());
}

Map* WorldGenerator::generateMap(int x, int y) {
	Map* retVal = new Map();
	retVal->init(MAP_WIDTH, MAP_HEIGHT);
	
	// Add the default empty tile
	Tile* emptyTile = new Tile();
	retVal->addTile(emptyTile);
	Tile* grassTile = new Tile("./data/images/GrassTile1.png", IS_WALKABLE | IS_MINABLE);
	retVal->addTile(grassTile);
	Tile* dirtTile = new Tile("./data/images/DirtTile.png");
	retVal->addTile(dirtTile);

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
				if (int(forestFactor*10000) % 10 < 3) {
					//retVal->setTile(x,y,2);
					//std::cout << "Adding a tree at " << x << "," << y << std::endl;
					/*Doodad* thisTree = entManager->doodadManager->addDoodadByType("Tree");
					point* thisPoint = Map::TileXYToTexXY(x,y);
					thisTree->moveToRealXY(thisPoint->realX,thisPoint->realY);
					delete thisPoint;*/
				}
			}
		}
	}
	return retVal;
}