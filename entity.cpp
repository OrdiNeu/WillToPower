#include "Entity.hpp"

void Entity::moveToRealXY(float x, float y) {
	realX = x;
	realY = y;
	point* tilePos = Map::TexXYToTileXY(x,y);
	tileX = tilePos->tileX;
	tileY = tilePos->tileY;
	delete tilePos;
}

void Entity::moveToTileXY(int x, int y) {
	tileX = x;
	tileY = y;
	point* tilePos = Map::TileXYToTexXY(x,y);
	realX = tilePos->realX;
	realY = tilePos->realY;
	delete tilePos;
}