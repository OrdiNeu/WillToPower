#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"

enum TAG_TYPES {
	IS_WALKABLE = 1,
	IS_IRON_ORE = 2
};

const int HALF_TILE_WIDTH = 16*X_SCALE;
const int HALF_TILE_HEIGHT = 8*Y_SCALE;
const int TILE_WIDTH = 2*HALF_TILE_WIDTH;
const int TILE_HEIGHT = 2*HALF_TILE_HEIGHT;

class Tile {
public:
	sf::Sprite spr;
	sf::Texture tex;
	std::string filename;
	int tags;
	Tile();
	Tile(std::string filename, int tags = 0);
	void render(sf::RenderTarget* screen, float x, float y);
	void update(float dt, int x, int y);
};

#endif