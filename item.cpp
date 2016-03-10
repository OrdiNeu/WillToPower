#include "item.hpp"

Item::Item() : Entity("UNIT_UNDEFINED","EMPTY",0,0) , tags(0) {
}

Item::Item(std::string uid, std::string filename, float x, float y, int tags) : Entity(uid, filename, x, y), tags(tags) {
}

Item* Item::clone(std::string newUID) {
	Item* newItem = new Item(newUID, filename, realX, realY, tags);
	return newItem;
}

void Item::update(float dt) {
}

bool Item::hasTag(int tag) {
	return (tags & tag) > 0;
}