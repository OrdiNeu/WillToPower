#include "mode_map_edit.hpp"
using namespace std;

ModeMapEdit::ModeMapEdit() {
	// Initialize the side bar
	sideBarBackground.setSize(sf::Vector2f(SIDEBAR_WIDTH, WINDOW_HEIGHT));
	sideBarBackground.setPosition(WINDOW_WIDTH-SIDEBAR_WIDTH, 0);
	curYOffset = 0.;
	curSelectedTile = NULL;
	rightClicked = false;
}

void ModeMapEdit::init() {
}

void ModeMapEdit::update(float dt, sf::RenderWindow* screen) {
	sf::Event e;
	while (screen->pollEvent(e)){
		if (e.type == sf::Event::Closed){
			screen->close();
		}
	}

	// If the mouse is over the right scrollbar...
	sf::Vector2i mousePos = sf::Mouse::getPosition(*screen);
	if (mousePos.x > WINDOW_WIDTH-SIDEBAR_WIDTH) {
		// Scroll the mouse if it is at either edge
		if (mousePos.y > 0 && mousePos.y < BUTTON_HEIGHT) {
			curYOffset += dt*SCROLL_SPEED;
		} else if (mousePos.y < WINDOW_HEIGHT && mousePos.y > WINDOW_HEIGHT - BUTTON_HEIGHT) {
			curYOffset -= dt*SCROLL_SPEED;
		}

		// Check for a click and switch currently selected tile if possible
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int tileClicked = (int) (mousePos.y - TILE_Y_OFFSET - curYOffset) / TILE_Y_SIZE;
			if (tileClicked >= 0 && tileClicked < curMap->getTileDict().size()) {
				curSelectedTile = curMap->getTileDict().at(tileClicked);
				cout << curSelectedTile << endl;
			}
		}
	} else {
		// Otherwise, we're in the map area
		// Check for clicks and swap the selected tile with the currently selected tile
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			point* clicked = Map::TexXYToTileXY(mousePos.x, mousePos.y);
			cout << "X: " << clicked->tileX << " Y: " << clicked->tileY << endl;
			curMap->setTile(clicked->tileX, clicked->tileY, curSelectedTile);
		}

		if (!rightClicked && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			rightClicked = true;
			std::vector<point*> route = AStarSearch(curMap, 0, 0, curMap->width-1, curMap->height-1);
			while (!route.empty()) {
				point* thisPoint = route.back();
				route.pop_back();
				curMap->setTile(thisPoint->tileX, thisPoint->tileY, 2);
				cout << thisPoint->tileX << "," << thisPoint->tileY << endl;
				delete thisPoint;
			}
		} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			rightClicked = false;
		}
	}
}

void ModeMapEdit::render(sf::RenderTarget* screen) {
	curMap->render(screen);
	entManager->unitManager->render(screen);

	// Draw the side bar
	screen->draw(sideBarBackground);

	// Get the different tiles, and render each one in the sidebar
	std::vector<Tile*> tileDict = curMap->getTileDict();
	for (unsigned int i = 0; i < tileDict.size(); i++) {
		Tile* thisTile = tileDict.at(i);
		thisTile->render(screen, WINDOW_WIDTH-TILE_X_OFFSET, i*TILE_Y_SIZE+TILE_Y_OFFSET+curYOffset);
	}
}