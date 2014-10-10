#include "map.hpp"
using namespace std;

Map::~Map() {
	for (unsigned int i = 0; i < tileDict.size(); i++) {
		tileDict.pop_back();
	}
	delete[] tiles;
}

void Map::update(float dt) {
}

void Map::render(sf::RenderTarget *screen) {
	screen->draw(mapSpr);
}

// Redraw the map texture
void Map::reRender() {
	mapTex.clear();
	// Draw each tile
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Draw the tile onto this texture
			tileDict.at(tiles[x][y])->render(mapTex, (x*2 + y%2)*HALF_TILE_WIDTH, y*HALF_TILE_HEIGHT);
		}
	}
	mapTex.display();	// Update the texture
	mapSpr.setTexture(mapTex.getTexture());
}

void Map::init(int width, int height) {
	// Set up the tiles
	this->width = width;
	this->height = height;
	tiles = new int*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new int[height];
		for (int y = 0; y < height; y++) {
			tiles[x][y] = 0;
		}
	}

	// Add the default empty tile
	Tile* emptyTile = new Tile();
	addTile(emptyTile);
	Tile* grassTile = new Tile("./data/images/GrassTile1.png");
	addTile(grassTile);
	mapTex.create(HALF_TILE_WIDTH*(2*width+1), HALF_TILE_HEIGHT*(height+1));
	mapSpr.setTexture(mapTex.getTexture());
	reRender();
}

Tile* Map::getTile(int x, int y) {
	return tileDict.at(tiles[x][y]);
}

void Map::addTile(Tile* tileToAdd) {
	tileDict.push_back(tileToAdd);
}