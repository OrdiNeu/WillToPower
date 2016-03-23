#ifndef DOODAD_HPP
#define DOODAD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "entity.hpp"

enum DOODAD_TAGS {
	NONE,
	PATHING_BLOCK,
	IS_TREE
};

// For those who don't know Blizzard terminology: doodads are background fixtures that do not have AI, and generally do less than units
// They may still have HP, but they definitely have no kinematics
class Doodad : public Entity {
public:
	Doodad();
	Doodad(std::string uid, std::string filename, int x, int y, int tags);
	Doodad* clone(std::string newUID);
	void update(float dt);
	void render(sf::RenderTarget* screen);
};

#endif