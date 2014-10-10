#include "map.hpp"

void Map::update(float dt) {
}

void Map::render(sf::RenderWindow &screen) {
	screen.draw(mapSpr);
}

void Map::init(int width, int height) {
	tiles = new int*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new int[height];
	}
	mapTex.update(mapImg);
	mapSpr.setTexture(mapTex);
}

Tile* Map::getTile(int x, int y) {
	return &(tileDict[tiles[x][y]]);
}