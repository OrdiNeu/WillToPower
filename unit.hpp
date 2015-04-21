#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "map.hpp"

enum UNIT_STATES {
	STATE_IDLE = 0,
	STATE_WALKING = 1
};

class Unit {
private:
	int halfWidth, height;
	float speed = 0.01;
public:
	static std::vector<Unit*> units;
	std::vector<point*> curPath;
	sf::Sprite spr;
	sf::Texture tex;
	std::string filename;
	Unit();
	Unit(std::string filename, int x, int y);
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void walkTo(std::vector<point*> path);
	float realX, realY;
	int tileX, tileY;
	float dx, dy;
	int state;
};

#endif