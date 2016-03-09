#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include <iostream>
#include <cstring>
#include <unordered_map>
#include "unit.hpp"
#include "unit_ai.hpp"
#include <sstream>
#include "manager.hpp"

class UnitManager : public Manager<Unit> {
public:
	std::vector<AI*> ais;
	void update(float dt);
	Unit* addNewEntByType(std::string type);
	void addEnt(AI* ai);
	void removeEnt(std::string uid);
	Map* curMap;
};

#endif