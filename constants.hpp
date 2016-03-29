#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

#define DEBUG_OUTPUT std::cout

const int X_SCALE = 2;
const int Y_SCALE = 2;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const int MAP_HEIGHT = 64;
const int MAP_WIDTH = 16;

// Moved over from tile.hpp because some objects need to know how to draw themselves
const int HALF_TILE_WIDTH = 16*X_SCALE;
const int HALF_TILE_HEIGHT = 8*Y_SCALE;
const int TILE_WIDTH = 2*HALF_TILE_WIDTH;
const int TILE_HEIGHT = 2*HALF_TILE_HEIGHT;
const int WALL_HEIGHT = 29*Y_SCALE;
const float TILE_DIST_DY_CONV_FACTOR = TILE_WIDTH*TILE_WIDTH/(TILE_HEIGHT*TILE_HEIGHT);

const int MAX_FPS=30;
const int WORLD_WIDTH_IN_MAPS = 20;
const int WORLD_LENGTH_IN_MAPS = 20;

// Colours
const int NUM_DEFAULT_COLORS = 2;
const sf::Color DEFAULT_TILE_COLORS[] = {sf::Color(255,255,255), sf::Color(255,0,0)};
enum defaultColors {
	COLOR_NONE,
	COLOR_TASKED,
};

#endif