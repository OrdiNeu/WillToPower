#include "unit.hpp"
using namespace std;

std::vector<Unit*> Unit::units;

Unit::Unit() {
	id = "UNIT_UNDEFINED";
}

Unit::Unit(std::string ID, std::string filename, int x, int y) : filename(filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		cout << "ERROR: Could not load " << filename << endl;
		return;
	};
	id = ID;
	realX = x;
	realY = y;
	halfWidth = (int) tex.getSize().x / 2;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
	units.push_back(this);
	state = STATE_IDLE;

	point* tilePos = Map::TexXYToTileXY(x,y);
	tileX = tilePos->tileX;
	tileY = tilePos->tileY;
	timeToComplete = 1000;
	skills = 1;
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