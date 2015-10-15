#include "map.hpp"
using namespace std;

Map::Map() {
	dirty = true;
}
Map::~Map() {
	while (!tileDict.empty()) {
		tileDict.pop_back();
	}
	delete[] tiles;
}

void Map::update(float dt) {
}

void Map::render(sf::RenderTarget *screen) {
	if (dirty)
		reRender();
	screen->draw(mapSpr);
}

// Redraw the map texture
void Map::reRender() {
	mapTex.clear();
	// Draw each tile
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Draw the tile onto this texture
			tileDict.at(tiles[x][y])->render(&mapTex, (x*2 + y%2)*HALF_TILE_WIDTH, y*HALF_TILE_HEIGHT);
		}
	}
	mapTex.display();	// Update the texture
	mapSpr.setTexture(mapTex.getTexture());
	dirty = false;
}

void Map::init(int width, int height) {
	// Set up the tiles
	this->width = width;
	this->height = height;
	tiles = new int*[width];
	for (int x = 0; x < width; x++) {
		tiles[x] = new int[height];
		for (int y = 0; y < height; y++) {
			tiles[x][y] = 1;
		}
	}

	mapTex.create(HALF_TILE_WIDTH*(2*width+1), HALF_TILE_HEIGHT*(height+1));
	mapSpr.setTexture(mapTex.getTexture());
	dirty = true;
}

Tile* Map::getTile(int x, int y) {
	return tileDict.at(tiles[x][y]);
}

void Map::addTile(Tile* tileToAdd) {
	tileDict.push_back(tileToAdd);
}

bool Map::inBounds(int x, int y) {
	return x >= 0 && y >= 0 && x < width && y < height;
}

void Map::setTile(int x, int y, Tile* tileToAdd) {
	// Look for this tile in the tileDict
	for (unsigned int i = 0; i < tileDict.size(); i++) {
		if (tileDict.at(i) == tileToAdd) {
			setTile(x,y,i);
			return;
		}
	}
}

void Map::setTile(int x, int y, int tileToAdd) {
	if (!inBounds(x,y))
		return;
	dirty = true;
	tiles[x][y] = tileToAdd;
}

// Converts a tileX, tileY to an X, Y relative to the texture's top left, where realX and realY is the center of tile (tileX, tileY)
point* Map::TileXYToTexXY(int tileX, int tileY) {
	point* retVal = new point;
	retVal->realX = (tileX*2 + tileY%2 + 1) * HALF_TILE_WIDTH;
	retVal->realY = (tileY + 1) * HALF_TILE_HEIGHT;
	retVal->tileX = tileX;
	retVal->tileY = tileY;
	return retVal;
}

point* Map::TexXYToTileXY(float texX, float texY) {
	point* retVal = new point;
	float realX = texX / TILE_WIDTH;
	float realY = texY / TILE_HEIGHT;
	bool oddY = (int(floor(realY + realX - 0.5) + floor(realY - realX - 0.5))) % 2 == 0;
	retVal->realX = texX;
	retVal->realY = texY;
	retVal->tileX = (int) (realX - 0.5*oddY);
	retVal->tileY = (int) (floor(realY - 0.5*oddY)*2 + oddY);	// There is likely a more elegant way of stating this, but I just spent 5 hours getting the math right
	return retVal;
}