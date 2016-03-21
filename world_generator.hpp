#ifndef WORLD_GENERATOR_HPP
#define WORLD_GENERATOR_HPP

#include <cstdlib>
#include <iostream>
#include "PerlinNoiseGenerator.hpp"
#include "map.hpp"
#include "entity_manager.hpp"
#include "constants.hpp"
#include "request_queue.hpp"
#include "material.hpp"
#include "xml_loader.hpp"

class WorldGenerator {
public:
	int seed;

	WorldGenerator(EntityManager* entManager, int seed = 0);
	~WorldGenerator();
	Map* getMap(int map_x, int map_y);
private:
	PerlinNoiseGenerator* forestryGen1;
	PerlinNoiseGenerator* forestryGen2;
	PerlinNoiseGenerator* forestryGen3;
	EntityManager* entManager;
	Map*** maps;

	void createGenerators();
	void addDefaultTiles(Map* map);
	Map* generateMap(int map_x, int map_y);
};

#endif