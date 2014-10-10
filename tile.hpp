#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>

enum TAG_TYPES {
	IS_WALKABLE = 1,
	IS_IRON_ORE = 2
};

const int HALF_TILE_WIDTH = 16;
const int HALF_TILE_HEIGHT = 16;

class Tile {
public:
	sf::Sprite sprite;
	int tags;
	void render(sf::RenderTarget &screen, int x, int y);
	void update(float dt, int x, int y);
};

#endif