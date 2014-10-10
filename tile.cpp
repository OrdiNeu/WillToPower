#include "tile.hpp"
using namespace std;

Tile::Tile() {
	tags = 0;
}

Tile::Tile(string filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		cout << "ERROR: Could not load " << filename << endl;
		return;
	};
	spr.setTexture(tex);
	spr.setScale(X_SCALE,Y_SCALE);
	tags = 0;
}

void Tile::render(sf::RenderTarget &screen, int x, int y) {
	spr.setPosition(x, y);
	screen.draw(spr);
}

void Tile::update(float dt, int x, int y) {

}