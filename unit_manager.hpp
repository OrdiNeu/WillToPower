#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include <iostream>
#include <cstring>
#include "unit.hpp"
#include "unit_ai.hpp"

class UnitManager {
public:
	std::vector<Unit*> units;
	std::vector<AI*> ais;
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addUnit(AI* ai);
	void removeUnit(std::string id);
	Map* curMap;
};

#endif