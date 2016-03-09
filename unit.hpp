#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "entity.hpp"

enum UNIT_STATES {
	STATE_IDLE = 0,
	STATE_FINISHED_JOB = 1,
	STATE_WALKING = 2,
	STATE_ACTING = 3
};

class Unit : public Entity {
private:
	float speed = 40;
	float timeToComplete;
	void init();
public:
	std::vector<point*> curPath;
	Unit();
	Unit(std::string uid, std::string filename);
	Unit(std::string uid, std::string filename, float x, float y);
	void walkTo(std::vector<point*> path);
	Unit* clone(std::string newUID);
	void update(float dt);
	void startTask(float timeToComplete);
	int state;
	int skills;
};

#endif