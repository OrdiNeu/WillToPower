#include "doodad.hpp"

Doodad::Doodad() : Entity("DOODAD_UNDEFINED","EMPTY",0,0) {}

Doodad::Doodad(std::string uid, std::string filename, int x, int y, int tags) : Entity(uid,filename,x,y), tags(tags) {
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

void Doodad::render(sf::RenderTarget* screen) {
	spr.setPosition(realX - tex.getSize().x, realY - (height*2));
	screen->draw(spr);
}