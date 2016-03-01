#include "Entity.hpp"

void Entity::moveToRealXY(float x, float y) {
	realX = x;
	realY = y;
}

void Entity::loadSprite(std::string filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		std::cout << "ERROR: Could not load " << filename << std::endl;
		return;
	};

	halfWidth = (int) tex.getSize().x / 2;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
	this->filename = filename;
}

void Entity::render(sf::RenderTarget* screen) {
	spr.setPosition(realX - halfWidth, realY - height);
	screen->draw(spr);
}