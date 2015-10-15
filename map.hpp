#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.hpp"
#include "constants.hpp"

class Map {
	friend class WorldGenerator;
private:
	int** tiles;
	std::vector<Tile*> tileDict;
	sf::RenderTexture mapTex;
	sf::Sprite mapSpr;
	bool dirty;
protected:
	void addTile(Tile* tileToAdd);
public:
	Map();
	~Map();
	void init(int width, int height);
	void update(float dt);
	void render(sf::RenderTarget* screen);
	void reRender();
	void setTile(int x, int y, Tile* tileToAdd);
	void setTile(int x, int y, int tileToAdd);
	Tile* getTile(int x, int y);
	bool inBounds(int x, int y);
	std::vector<Tile*> getTileDict(){ return tileDict; };
	int width, height;

	static point* TexXYToTileXY(float texX, float texY);
	static point* TileXYToTexXY(int x, int y);
};

#endif