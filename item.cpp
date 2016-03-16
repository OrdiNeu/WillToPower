#include "item.hpp"

Item::Item() : Entity("UNIT_UNDEFINED","EMPTY",0,0,0), tasked(false), inInventory(false) {
}

Item::Item(std::string uid, std::string filename, float x, float y, int tags) : Entity(uid, filename, x, y, tags), tasked(false), inInventory(false) {
}

Item* Item::clone(std::string newUID) {
	Item* newItem = new Item(newUID, filename, realX, realY, tags);
	return newItem;
}

void Item::update(float dt) {
}

void Item::render(sf::RenderTarget* screen) {
	if (!inInventory) {
		spr.setPosition(realX - halfWidth, realY - height);
		screen->draw(spr);
	}
}