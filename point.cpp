#include "point.hpp"

// Converts a tileX, tileY to an X, Y relative to the texture's top left, where realX and realY is the center of tile (tileX, tileY)
point TileXYToTexXY(int tileX, int tileY) {
	point retVal;
	retVal.realX = (tileX*2 + tileY%2 + 1) * HALF_TILE_WIDTH;
	retVal.realY = (tileY + 1) * HALF_TILE_HEIGHT;
	retVal.tileX = tileX;
	retVal.tileY = tileY;
	return retVal;
}

point TexXYToTileXY(float texX, float texY) {
	point retVal;
	float realX = texX / TILE_WIDTH;
	float realY = texY / TILE_HEIGHT;
	bool oddY = (int(floor(realY + realX - 0.5) + floor(realY - realX - 0.5))) % 2 == 0;
	retVal.realX = texX;
	retVal.realY = texY;
	retVal.tileX = (int) floor(realX - 0.5*oddY);
	retVal.tileY = (int) (floor(realY - 0.5*oddY)*2 + oddY);	// There is likely a more elegant way of stating this, but I just spent 5 hours getting the math right
	return retVal;
}