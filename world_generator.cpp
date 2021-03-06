#include "world_generator.hpp"

const float PerlinScalingFactor1 = 20.0;
const float PerlinScalingFactor2 = 8.0;
const float PerlinScalingFactor3 = 3.0;
const float PerlinWeightFactor1 = 2;
const float PerlinWeightFactor2 = 2;
const float PerlinWeightFactor3 = 2;

WorldGenerator::WorldGenerator(EntityManager* entManager, int seed) : seed(seed), entManager(entManager) {
	srand(seed);
	createGenerators();
	maps = new Map**[WORLD_LENGTH_IN_MAPS];
	for (int x = 0; x < WORLD_LENGTH_IN_MAPS; x++) {
		maps[x] = new Map*[WORLD_WIDTH_IN_MAPS];
		for (int y = 0; y < WORLD_WIDTH_IN_MAPS; y++) {
			maps[x][y] = NULL;
		}
	}
}

void WorldGenerator::createGenerators() {
	forestryGen1 = new PerlinNoiseGenerator(rand());
	forestryGen2 = new PerlinNoiseGenerator(rand());
	forestryGen3 = new PerlinNoiseGenerator(rand());
}


WorldGenerator::~WorldGenerator() {
	delete forestryGen1;
	delete forestryGen2;
	delete forestryGen3;
	for (int x = 0; x < WORLD_LENGTH_IN_MAPS; x++) {
		delete maps[x];
	}	
}
void WorldGenerator::loadMaterials(Map* map) {
	XmlLoader::loadMaterials(entManager->doodadManager, map, "./data/materials.xml");
	Doodad tree = Doodad("TREE", "./data/images/Tree.png", 0, 0, IS_TREE | PATHING_BLOCK);
	entManager->doodadManager->addNewEntType("Tree", tree);
	Item item = Item("WOOD", "./data/images/skills/HealIcon.png", 0, 0, IS_WOOD);
	entManager->itemManager->addNewEntType("Wood", item);
}

Map* WorldGenerator::generateMap(int map_x, int map_y) {
	Map* retVal = new Map();
	retVal->init(MAP_WIDTH, MAP_HEIGHT);
	
	loadMaterials(retVal);

	// Get the forest layer
	for (int x = map_x; x < retVal->width+map_x; x++) {
		for (int y = map_y; y < retVal->height+map_y; y++) {
			double forestFactor = forestryGen3->get(float(x)/PerlinScalingFactor3, float(y)/PerlinScalingFactor3)*PerlinWeightFactor3;
			forestFactor +=  forestryGen2->get(float(x)/PerlinScalingFactor2, float(y)/PerlinScalingFactor2)*PerlinWeightFactor2;
			forestFactor +=  forestryGen1->get(float(x)/PerlinScalingFactor1, float(y)/PerlinScalingFactor1)*PerlinWeightFactor1;
			if (forestFactor > 0) {
				// This is a forest-y region
				retVal->setTile(x,y,0);
				// If the 6th digit is a 2, 1, or 0, put a tree here
				if (rand() % 10 < 2) {
					point thisPoint = TileXYToTexXY(x,y);
					RequestQueues::entityRequests.push_back(entRequest::newEntRequest("Tree", thisPoint.realX, thisPoint.realY, ENT_TYPE_DOODAD));
				}
			} else if (forestFactor < -0.5) {
				// This is a dry region
				retVal->setTile(x,y,1);
				if (rand() % 2 == 0) {
					point thisPoint = TileXYToTexXY(x,y);
					RequestQueues::entityRequests.push_back(entRequest::newEntRequest("dirt_0", thisPoint.realX, thisPoint.realY, ENT_TYPE_DOODAD));
				}
			} else {
				retVal->setTile(x,y,0);
			}
		}
	}
	return retVal;
}

Map* WorldGenerator::getMap(int map_x, int map_y) {
	if (maps[map_x][map_y] == NULL) {
		maps[map_x][map_y] = generateMap(map_x,map_y);
	}
	return maps[map_x][map_y];
}