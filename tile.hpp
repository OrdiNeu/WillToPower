#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>

enum TAG_TYPES {
	IS_WALKABLE = 1,
	IS_IRON_ORE = 2
}

class Tile {
	sf::Sprite sprite;
	int tags;
};

#endif