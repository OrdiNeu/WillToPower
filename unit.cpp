#include "unit.hpp"
using namespace std;

Unit::Unit() : Entity("UNIT_UNDEFINED","EMPTY",0,0) {
	init();
}

Unit::Unit(std::string uid, std::string filename) : Entity(uid, filename, 0, 0) {
	init();
}

Unit::Unit(std::string uid, std::string filename, float x, float y) : Entity(uid, filename, x, y){
	init();
}

void Unit::init(){
	state = STATE_IDLE;
	timeToComplete = 1000;
	skills = 1;
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
				state = STATE_FINISHED_JOB;
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