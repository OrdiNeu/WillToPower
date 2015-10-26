#include "doodad.hpp"

Doodad::Doodad() {}

Doodad::Doodad(std::string ID, std::string filename, int x, int y, int tags) : filename(filename), tags(tags) {
	id = ID;	
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		std::cout << "ERROR: Could not load " << filename << std::endl;
		return;
	};
	id = ID;
	realX = x;
	realY = y;
	halfWidth = (int) tex.getSize().x / 2;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);

	point* tilePos = Map::TexXYToTileXY(x,y);
	tileX = tilePos->tileX;
	tileY = tilePos->tileY;
	delete tilePos;
}

void Doodad::render(sf::RenderTarget* screen) {
	spr.setPosition(realX - halfWidth, realY - height);
	screen->draw(spr);
}

Doodad* Doodad::clone() {
	Doodad* newDoodad = new Doodad(id, filename, realX, realY, tags);
	return newDoodad;
}

void Doodad::update(float dt) {
	// Empty for now
}