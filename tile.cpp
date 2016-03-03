#include "tile.hpp"
using namespace std;

Tile::Tile() {
	tags = 0;
}

Tile::Tile(string filename, int tags) : filename(filename), tags(tags) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		cout << "ERROR: Could not load " << filename << endl;
		return;
	};
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
}

void Tile::render(sf::RenderTarget* screen, float x, float y) {
	spr.setPosition(x, y/*-tex.getSize().y*/);
	screen->draw(spr);
}

void Tile::update(float dt, int x, int y) {

}

bool Tile::hasTag(int tag) {
	return (tags & tag) > 0;
}