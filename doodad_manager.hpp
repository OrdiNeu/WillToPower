#ifndef DOODAD_MANAGER_HPP
#define DOODAD_MANAGER_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include "doodad.hpp"
#include "map.hpp"
#include "manager.hpp"
#include "point.hpp"

class DoodadManager : public Manager<Doodad> {
public:
	std::vector<Doodad*> getDoodadsAtPoint(int x, int y);	// Expensive to use
	void addEnt(Doodad* ent);
	Doodad* removeEnt(std::string uid);
};

#endif