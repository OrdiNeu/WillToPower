#include "material.hpp"

int Material::getRandomTileID() {
	return tileIDs[rand() % tileIDs.size()];
}

std::string Material::getRandomWallID() {
	return wallIDs[rand() % wallIDs.size()];
}