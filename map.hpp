#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include <iostream>

class Map {
	private:
		int** tiles;
		std::vector<Tile> tileDict;
		int width, height;
		sf::RenderTexture mapTex;
		sf::Sprite mapSpr;
		void addTile();
	public:
		void init(int width, int height);
		void update(float dt);
		void render(sf::RenderWindow &screen);
		void reRender();
		Tile* getTile(int x, int y);
};

#endif