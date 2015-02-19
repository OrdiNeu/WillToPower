#ifndef MODE_MAP_EDIT
#define MODE_MAP_EDIT
#include "mode.hpp"
#include "constants.hpp"
#include <SFML/Graphics.hpp>

class ModeMapEdit : public Mode {
private:
	sf::RectangleShape sideBarBackground;
	float curYOffset;
	Tile* curSelectedTile;
public:
	ModeMapEdit();
	void init();
	void update(float dt, sf::RenderWindow* screen);
	void render(sf::RenderTarget* screen);
};

const int SIDEBAR_WIDTH = 100;
const int BUTTON_HEIGHT = 20;
const int TILE_X_OFFSET = (int) (SIDEBAR_WIDTH/2) + HALF_TILE_WIDTH;
const int TILE_Y_OFFSET = BUTTON_HEIGHT;
const int TILE_Y_SIZE = HALF_TILE_HEIGHT*2 + 10;
const int SCROLL_SPEED = 100;
#endif