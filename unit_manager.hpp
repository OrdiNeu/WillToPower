#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include <iostream>
#include <cstring>
#include "unit.hpp"
#include "map.hpp"
#include "a_star.hpp"

// Define some stuff to control unit movement behaviour - should be moved to AI.hpp when possible
#define AI_MOVE_CENTER_OF_TILE
const float DISTANCE_FROM_CENTER = 5;
const float DISTANCE_FROM_CENTER_SQ = DISTANCE_FROM_CENTER * DISTANCE_FROM_CENTER;

class UnitManager {
	static std::vector<Unit*> units;
public:
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addUnit(Unit* unit);
	Map* curMap;
};

#endif