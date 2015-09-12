#ifndef DOODAD_MANAGER_HPP
#define DOODAD_MANAGER_HPP

#include <iostream>
#include <cstring>
#include "doodad.hpp"
#include <unordered_map>

class DoodadManager {
public:
	std::vector<Doodad*> doodads;
	std::unordered_map<std::string, Doodad> doodad_library;
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addDoodad(Doodad* doodad);
	Doodad* addDoodadByType(std::string type);
	void removeDoodad(std::string id);
	Map* curMap;
};

#endif