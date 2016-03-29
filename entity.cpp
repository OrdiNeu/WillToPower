#include "Entity.hpp"

Entity::Entity(std::string uid, std::string filename, float realX, float realY, int tags) : uid(uid), filename(filename), realX(realX), realY(realY), tags(tags) {
	this->tags = tags;
	loadSprite(filename);
}

Entity::~Entity() {
}

void Entity::moveToRealXY(float x, float y) {
	realX = x;
	realY = y;
}

void Entity::loadSprite(std::string filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		DEBUG_OUTPUT << "ERROR: Could not load " << filename << std::endl;
		return;
	};

	halfWidth = (int) tex.getSize().x / 2;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
}

void Entity::render(sf::RenderTarget* screen) {
	spr.setPosition(realX - halfWidth, realY - height);
	screen->draw(spr);
}

bool Entity::hasTags(int tags) {
	return (this->tags & tags) == tags;
}