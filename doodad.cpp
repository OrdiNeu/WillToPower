#include "doodad.hpp"

Doodad::Doodad() {}

Doodad::Doodad(std::string uid, std::string filename, int x, int y, int tags) : filename(filename), tags(tags) {
	this->uid = uid;
	realX = x;
	realY = y;
	loadSprite(filename);
}

Doodad* Doodad::clone() {
	Doodad* newDoodad = new Doodad(uid, filename, realX, realY, tags);
	return newDoodad;
}

void Doodad::update(float dt) {
	// Empty for now
}

bool Doodad::hasTag(int tag) {
	return (tags & tag) > 0;
}