#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include <iostream>
#include <cstring>
#include "unit.hpp"
#include "unit_ai.hpp"

class UnitManager {
private:
	static std::vector<Unit*> units;
	static std::vector<AI*> ais;
public:
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addUnit(AI* ai);
	Map* curMap;
};

#endif