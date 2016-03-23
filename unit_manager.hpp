#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include <iostream>
#include <cstring>
#include <unordered_map>
#include "unit.hpp"
#include "unit_ai.hpp"
#include <sstream>
#include "manager.hpp"
#include "point.hpp"

class EntityManager;

class UnitManager : public Manager<Unit> {
friend EntityManager;
public:
	std::vector<AI*> ais;
	void update(float dt);
	Unit* addNewEntByType(std::string type, float x, float y);
	void addEnt(AI* ai);
	Unit* removeEnt(std::string uid);
	Map* curMap;
};

#endif