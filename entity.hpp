#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

class Entity {
public:
	float realX, realY;
	std::string uid;			// Should be unique
	float dx, dy;

	void moveToRealXY(float x, float y);
};

#endif