#ifndef WORLD_GENERATOR_HPP
#define WORLD_GENERATOR_HPP

#include <cstdlib>
#include <iostream>
#include "PerlinNoiseGenerator.hpp"
#include "map.hpp"
#include "entity_manager.hpp"
#include "constants.hpp"
#include "request_queue.hpp"

class WorldGenerator {
public:
	WorldGenerator(EntityManager* entManager);
	WorldGenerator(int seed, EntityManager* entManager);
	Map* generateMap(int map_x, int map_y);
	int seed;
	void addDefaultTiles(Map* map);
private:
	PerlinNoiseGenerator* forestryGen1;
	PerlinNoiseGenerator* forestryGen2;
	PerlinNoiseGenerator* forestryGen3;
	EntityManager* entManager;
	void createGenerators();
};

#endif