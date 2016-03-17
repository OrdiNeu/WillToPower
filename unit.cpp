#include "unit.hpp"
using namespace std;

Unit::Unit() : Entity("UNIT_UNDEFINED","EMPTY",0,0,0) {
	init();
}

Unit::Unit(std::string uid, std::string filename) : Entity(uid, filename, 0, 0, 0) {
	init();
}

Unit::Unit(std::string uid, std::string filename, float x, float y, int tags) : Entity(uid, filename, x, y, tags){
	init();
}

Unit::~Unit() {
	// Drop all items
	for (typename std::vector<Item*>::iterator it = inv.begin() ; it != inv.end(); ++it) {
		(*it)->realX = realX;
		(*it)->realY = realY;
		(*it)->inInventory = false;
	}
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
	Unit* newUnit = new Unit(newUID, filename, realX, realY, tags);
	newUnit->skills = skills;
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
		case STATE_ACTING: {
			timeToComplete -= dt;
			if (timeToComplete < 0) {
				state = STATE_FINISHED_JOB;
			}
			break;
		}
		case STATE_IDLE:
		default:
		break;
	}
}

void Unit::startTask(float timeToComplete) {
	state = STATE_ACTING;
	this->timeToComplete = timeToComplete;
}