#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>

enum MATERIAL_TAGS {
	MAT_IS_WOOD = 1,
	MAT_IS_FIREPROOF = 2
};

// Contains the IDs to convert between tile, wall, and object
struct Material {
	int tileID;
	int wallID;
	std::string itemID;
	int tags;
};

#endif