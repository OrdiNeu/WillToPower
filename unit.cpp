#include "unit.hpp"
using namespace std;

Unit::Unit() {
	uid = "UNIT_UNDEFINED";
}

Unit::Unit(std::string uid, std::string filename) : filename(filename) {
	Unit(uid, filename, 0, 0);
}

Unit::Unit(std::string uid, std::string filename, float x, float y) : filename(filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		cout << "ERROR: Could not load " << filename << endl;
		return;
	};
	uid = uid;
	halfWidth = (int) tex.getSize().x / 2;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
	state = STATE_IDLE;

	timeToComplete = 1000;
	skills = 1;
	moveToRealXY(x, y);
}

void Unit::render(sf::RenderTarget* screen) {
	spr.setPosition(realX - halfWidth, realY - height);
	screen->draw(spr);
}

void Unit::walkTo(std::vector<point*> path) {
	curPath = path;
	state = STATE_WALKING;
}

Unit* Unit::clone(std::string newUID) {
	Unit* newUnit = new Unit(newUID, filename, realX, realY);
	return newUnit;
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
				dx = 2*speed*dt;
			} else if (realX > nextLoc->realX) {
				dx = -2*speed*dt;
			}
			if (realY < nextLoc->realY) {
				dy = speed*dt;
			} else if (realY > nextLoc->realY) {
				dy = -speed*dt;
			}
			break;
		}
		case STATE_IDLE:
		default:
		break;
	}
}