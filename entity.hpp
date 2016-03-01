#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <iostream>

class Entity {
protected:
	int halfWidth, height;
public:
	std::string filename;
	sf::Sprite spr;
	sf::Texture tex;
	float realX, realY;
	std::string uid;			// Should be unique
	float dx, dy;

	void loadSprite(std::string filename);
	void moveToRealXY(float x, float y);
	void render(sf::RenderTarget* screen);
	virtual void update(float dt) {};
};

#endif