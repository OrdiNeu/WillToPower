#include "world_generator.hpp"

const float PerlinScalingFactor = 5.0;

WorldGenerator::WorldGenerator(int seed, EntityManager* entManager) : seed(seed), entManager(entManager) {
	srand(seed);
	forestryGen = new PerlinNoiseGenerator(rand()); //TODO: Read up on "shadowing a parameter"
}

WorldGenerator::WorldGenerator(EntityManager* entManager) : entManager(entManager) {
	forestryGen = new PerlinNoiseGenerator(rand());
}

Map* WorldGenerator::generateMap(int x, int y) {
	Map* retVal = new Map();
	retVal->init(MAP_WIDTH, MAP_HEIGHT);
	
	// Add the default empty tile
	Tile* emptyTile = new Tile();
	retVal->addTile(emptyTile);
	Tile* grassTile = new Tile("./data/images/GrassTile1.png", IS_WALKABLE);
	retVal->addTile(grassTile);
	Tile* dirtTile = new Tile("./data/images/DirtTile.png");
	retVal->addTile(dirtTile);

	// Get the forest layer
	for (int x = 0; x < retVal->width; x++) {
		for (int y = 0; y < retVal->height; y++) {
			double forestFactor = forestryGen->get(float(x)/PerlinScalingFactor, float(y)/PerlinScalingFactor);
			if (forestFactor > 0) {
				// This is a forest-y region
				retVal->setTile(x,y,1);
				// If the 6th digit is a 2, 1, or 0, put a tree here
				if (int(forestFactor*10000) % 10 < 3) {
					/*Doodad* thisTree = entManager->doodadManager->addDoodadByType("Tree");
					thisTree->moveToTileXY(x,y);*/
				}
			}
		}
	}
	return retVal;
}