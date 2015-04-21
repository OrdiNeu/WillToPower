#include "unit.hpp"
using namespace std;

std::vector<Unit*> Unit::units;

Unit::Unit() {
}

Unit::Unit(std::string filename, int x, int y) : filename(filename), realX(x), realY(y) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		cout << "ERROR: Could not load " << filename << endl;
		return;
	};
	halfWidth = (int) tex.getSize().x / 2;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
	units.push_back(this);
	state = STATE_IDLE;

	point* tilePos = Map::TexXYToTileXY(x,y);
	tileX = tilePos->tileX;
	tileY = tilePos->tileY;
	delete tilePos;
}

void Unit::render(sf::RenderTarget* screen) {
	spr.setPosition(realX - halfWidth, realY - height);
	screen->draw(spr);
}

void Unit::walkTo(std::vector<point*> path) {
	curPath = path;
	state = STATE_WALKING;
}

void Unit::update(float dt) {
	// Determine what to do depending on state
	switch (state) {
		case STATE_WALKING: {
			if (curPath.empty()) {
				state = STATE_IDLE;
				dx = 0;
				dy = 0;
				break;
			}
			point* nextLoc = curPath.back();
			if (realX < nextLoc->realX) {
				dx = 2*speed;
			} else if (realX > nextLoc->realX) {
				dx = -2*speed;
			}
			if (realY < nextLoc->realY) {
				dy = speed;
			} else if (realY > nextLoc->realY) {
				dy = -speed;
			}
			break;
		}
		case STATE_IDLE:
		default:
		break;
	}
}