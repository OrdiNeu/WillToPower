#ifndef POINT_HPP
#define POINT_HPP

#include "constants.hpp"
#include <cmath>

struct point {
	int tileX;
	int tileY;
	int realX;
	int realY;
};

// Converts a tileX, tileY to an X, Y relative to the texture's top left, where realX and realY is the center of tile (tileX, tileY)
point TileXYToTexXY(int tileX, int tileY);
point TexXYToTileXY(float texX, float texY);

#endif