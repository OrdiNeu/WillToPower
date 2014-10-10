#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include <iostream>

class Map {
	private:
		Tile** tiles;
	public:
		void update(float dt);
		void render(sf::RenderWindow* screen);
};

#endif