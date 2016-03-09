#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include <iostream>
#include <cstring>
#include <unordered_map>
#include "unit.hpp"
#include "unit_ai.hpp"
#include <sstream>

class UnitManager {
public:
	std::vector<Unit*> units;
	std::unordered_map<std::string, Unit> unit_library;
	std::unordered_map<std::string, int> num_units_created;
	std::vector<AI*> ais;
	Unit* lastCreatedUnit;
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void getNewUnitByType(std::string type);
	Unit* addNewUnitByType(std::string type);
	void addNewUnitType(std::string type, Unit newUnit);
	void addUnit(AI* ai);
	void removeUnit(std::string uid);
	Map* curMap;
};

#endif