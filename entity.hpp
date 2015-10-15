#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "map.hpp"

class Entity {
public:
	float realX, realY;
	int tileX, tileY;
	std::string id;			// Should be unique
	float dx, dy;

	void moveToRealXY(float x, float y);
	void moveToTileXY(int x, int y);
};

#endif