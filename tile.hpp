#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "entity.hpp"

enum TILE_TAGS {
	IS_WALKABLE = 1,
	IS_MINABLE = 2,
	FLOOR = 2 << 7,
	WALL = 2 << 8
};

class Tile : public Entity {
public:
	int tags;
	int lastColor;
	Tile();
	Tile(std::string filename, int tags = 0);
	void render(sf::RenderTarget* screen, float x, float y);
	void update(float dt, int x, int y);
	bool hasTag(int tag);
};

#endif