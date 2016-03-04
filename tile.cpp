#include "tile.hpp"
using namespace std;

Tile::Tile() : Entity("0", "EMPTY", 0, 0), tags(0) {
}

Tile::Tile(string filename, int tags) : Entity("0", filename, 0, 0), tags(tags) {
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