#ifndef DOODAD_HPP
#define DOODAD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "entity.hpp"

enum DOODAD_TAGS {
	NONE,
	IS_TREE
};

// For those who don't know Blizzard terminology: doodads are background fixtures that do not have AI, and generally do less than units
// They may still have HP, but they definitely have no kinematics
class Doodad : public Entity {
public:
	std::string filename;
	int tags;
	Doodad();
	Doodad(std::string uid, std::string filename, int x, int y, int tags);
	Doodad* clone();
	void update(float dt);
	bool hasTag(int tag);
};

#endif