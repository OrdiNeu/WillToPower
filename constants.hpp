#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

struct point {
	int tileX;
	int tileY;
	int realX;
	int realY;
};

const int X_SCALE = 2;
const int Y_SCALE = 2;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const int MAP_HEIGHT = 32;
const int MAP_WIDTH = 32;

// Moved over from tile.hpp because some objects need to know how to draw themselves
const int HALF_TILE_WIDTH = 16*X_SCALE;
const int HALF_TILE_HEIGHT = 8*Y_SCALE;
const int TILE_WIDTH = 2*HALF_TILE_WIDTH;
const int TILE_HEIGHT = 2*HALF_TILE_HEIGHT;

const int MAX_FPS=30;

#endif