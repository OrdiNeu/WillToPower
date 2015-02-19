#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include <iostream>

struct point {
	int x;
	int y;
};

class Map {
	private:
		int** tiles;
		std::vector<Tile*> tileDict;
		sf::RenderTexture mapTex;
		sf::Sprite mapSpr;
		void addTile(Tile* tileToAdd);
		bool dirty;
	public:
		~Map();
		void init(int width, int height);
		void update(float dt);
		void render(sf::RenderTarget* screen);
		void reRender();
		void setTile(int x, int y, Tile* tileToAdd);
		void setTile(int x, int y, int tileToAdd);
		point* TexXYToTileXY(float texX, float texY);
		Tile* getTile(int x, int y);
		bool inBounds(int x, int y);
		std::vector<Tile*> getTileDict(){ return tileDict; };
		int width, height;
};

#endif