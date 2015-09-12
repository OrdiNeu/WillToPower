#include "unit.hpp"
using namespace std;

Unit::Unit() {
	id = "UNIT_UNDEFINED";
}

Unit::Unit(std::string ID, std::string filename) : filename(filename) {
	Unit(ID, filename, 0, 0);
}

Unit::Unit(std::string ID, std::string filename, float x, float y) : filename(filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		cout << "ERROR: Could not load " << filename << endl;
		return;
	};
	id = ID;
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

Unit* Unit::clone() {
	Unit* newUnit = new Unit(id, filename, realX, realY);
	return newUnit;
}

void Unit::moveToRealXY(float x, float y) {
	realX = x;
	realY = y;
	point* tilePos = Map::TexXYToTileXY(x,y);
	tileX = tilePos->tileX;
	tileY = tilePos->tileY;
	delete tilePos;
}

void Unit::moveToTileXY(int x, int y) {
	tileX = x;
	tileY = y;
	point* tilePos = Map::TileXYToTexXY(x,y);
	realX = tilePos->realX;
	realY = tilePos->realY;
	delete tilePos;
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
			timeToComplete -= dt;
			if (timeToComplete < 0) {
				// See if there's a job available
				for (Job thisJob : JobQueue::jobQueue) {
					// Ignore this job if it is suspended or if we lack a requisite skill
					if (thisJob.suspended) { continue; }
					bool unavailable = false;
					for (int skillID = 0; skillID <= NUM_SKILLS; skillID++) {
						if (!((skills & skillID) == skillID)) {
							unavailable = true;
							break;
						}
					}
					if (unavailable) { continue; }

					// We can do this job: we act depending on what type of job it is
					switch (thisJob.type) {
						case JOB_TYPE_MINING:
						break;
					}
				}
			}
		default:
		break;
	}
}