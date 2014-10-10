#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include <iostream>

class Map {
	private:
		int** tiles;
		Tile* tileDict;
		int width, height;
		sf::Image mapImg;
		sf::Texture mapTex;
		sf::Sprite mapSpr;
	public:
		void init(int width, int height);
		void update(float dt);
		void render(sf::RenderWindow &screen);
		Tile* getTile(int x, int y);
};

#endif