#include "tile.hpp"

Tile::Tile() : Entity("0", "EMPTY", 0, 0, 0) {
}

Tile::Tile(std::string filename, int tags) : Entity("0", filename, 0, 0, tags) {
}

void Tile::render(sf::RenderTarget* screen, float x, float y) {
	//int yoffset = hasTag(WALL)*(WALL_HEIGHT-TILE_HEIGHT);
	spr.setPosition(x, y /*- yoffset*/);
	screen->draw(spr);
}

void Tile::update(float dt, int x, int y) {

}

bool Tile::hasTag(int tag) {
	return (tags & tag) > 0;
}