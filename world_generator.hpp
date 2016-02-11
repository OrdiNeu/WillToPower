#ifndef WORLD_GENERATOR_HPP
#define WORLD_GENERATOR_HPP

#include <cstdlib>
#include <iostream>
#include "PerlinNoiseGenerator.hpp"
#include "map.hpp"
#include "entity_manager.hpp"
#include "constants.hpp"

class WorldGenerator {
public:
	WorldGenerator(EntityManager* entManager);
	WorldGenerator(int seed, EntityManager* entManager);
	Map* generateMap(int x, int y);
	int seed;
private:
	PerlinNoiseGenerator* forestryGen1;
	PerlinNoiseGenerator* forestryGen2;
	PerlinNoiseGenerator* forestryGen3;
	EntityManager* entManager;
};

#endif