#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "entity.hpp"

enum ITEM_TAGS {
	IS_WOOD = 1
};

// Items: things that units may pick up
class Item : public Entity {
public:
	int tags;
	Item();
	Item(std::string uid, std::string filename, float x, float y, int tags);
	Item* clone(std::string newUID);
	void update(float dt);
	bool hasTag(int tag);
};

#endif