#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <iostream>

class Entity {
public:
	Entity(std::string uid, std::string filename, float realX, float realY);
	std::string uid;			// Should be unique
	std::string filename;
	sf::Sprite spr;
	sf::Texture tex;
	float realX, realY;
	float dx, dy;

	void loadSprite(std::string filename);
	void moveToRealXY(float x, float y);
	virtual void render(sf::RenderTarget* screen);
	virtual void update(float dt) {};
protected:
	int halfWidth, height;
};

#endif