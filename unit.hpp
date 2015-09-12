#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "job_queue.hpp"

enum UNIT_STATES {
	STATE_IDLE = 0,
	STATE_WALKING = 1
};

class Unit : public Entity {
private:
	int halfWidth, height;
	float speed = 0.03;
	float timeToComplete;
public:
	std::vector<point*> curPath;
	sf::Sprite spr;
	sf::Texture tex;
	std::string filename;
	Unit();
	Unit(std::string ID, std::string filename);
	Unit(std::string ID, std::string filename, float x, float y);
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void walkTo(std::vector<point*> path);
	void moveToRealXY(float x, float y);
	void moveToTileXY(int x, int y);
	Unit* clone();
	int state;
	int skills;
};

#endif