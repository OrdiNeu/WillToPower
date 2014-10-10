#include "map.hpp"

void Map::update(float dt) {
	
}

void Map::render(sf::RenderWindow* screen) {

}

void Map::init(int width, int height) {
	tiles = Tile[width][height];
}

Tile* Map::getTile(int x, int y) {
	return tileDict[tiles[x][y]];
}