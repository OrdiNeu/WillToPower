#include "map.hpp"

void Map::update(float dt) {
}

void Map::render(sf::RenderWindow &screen) {
	screen.draw(mapSpr);
}

// Redraw the map texture
void Map::reRender() {
	mapTex.clear();
	// Draw each tile
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			// Draw the tile onto this texture
			tileDict[tiles[x][y]].render(mapTex, x, y);
		}
	}
	mapSpr.setTexture(mapTex.getTexture());
}

void Map::init(int width, int height) {
	tiles = new int*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new int[height];
		for (int y = 0; y < height; y++) {
			tiles[x][y] = 0;
		}
	}
	mapTex.create(HALF_TILE_WIDTH*(2*width+1), HALF_TILE_HEIGHT*(height+1));
	mapSpr.setTexture(mapTex.getTexture());
}

Tile* Map::getTile(int x, int y) {
	return &(tileDict.at(tiles[x][y]));
}