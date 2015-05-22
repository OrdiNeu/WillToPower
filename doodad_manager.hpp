#ifndef DOODAD_MANAGER_HPP
#define DOODAD_MANAGER_HPP

#include <iostream>
#include <cstring>
#include "doodad.hpp"

class DoodadManager {
public:
	std::vector<Doodad*> doodads;
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addDoodad(Doodad* doodad);
	void removeDoodad(std::string id);
	Map* curMap;
};

#endif