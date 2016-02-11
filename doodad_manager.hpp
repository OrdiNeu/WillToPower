#ifndef DOODAD_MANAGER_HPP
#define DOODAD_MANAGER_HPP

#include <iostream>
#include <cstring>
#include "doodad.hpp"
#include <unordered_map>
#include "map.hpp"

class DoodadManager {
public:
	std::vector<Doodad*> doodads;
	std::unordered_map<std::string, Doodad> doodad_library;
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addDoodad(Doodad* doodad);
	Doodad* addDoodadByType(std::string type);
	void removeDoodad(std::string uid);
	std::vector<Doodad*> getDoodadsAtPoint(int x, int y);	// Expensive to use
	Map* curMap;
};

#endif