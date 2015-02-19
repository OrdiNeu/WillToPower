#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"

class Unit {
private:
	int halfWidth, height;
public:
	static std::vector<Unit*> units;
	sf::Sprite spr;
	sf::Texture tex;
	std::string filename;
	Unit();
	Unit(std::string filename, int x, int y);
	void render(sf::RenderTarget* screen);
	void update(float dt);
	int x, y;
};

#endif