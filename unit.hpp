#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "entity.hpp"

enum UNIT_STATES {
	STATE_IDLE = 0,
	STATE_FINISHED_JOB = 1,
	STATE_WALKING = 2
};

class Unit : public Entity {
private:
	float speed = 40;
	float timeToComplete;
public:
	std::vector<point*> curPath;
	Unit();
	Unit(std::string uid, std::string filename);
	Unit(std::string uid, std::string filename, float x, float y);
	void walkTo(std::vector<point*> path);
	Unit* clone(std::string newUID);
	int state;
	int skills;
};

#endif