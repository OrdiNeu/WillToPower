#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include <iostream>
#include <cstring>
#include "unit.hpp"
#include "map.hpp"
#include "a_star.hpp"

class UnitManager {
	static std::vector<Unit*> units;
public:
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addUnit(Unit* unit);
	Map* curMap;
};

#endif