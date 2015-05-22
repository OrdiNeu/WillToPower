#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

class Entity {
public:
	float realX, realY;
	int tileX, tileY;
	std::string id;			// Should be unique
	float dx, dy;
};

#endif