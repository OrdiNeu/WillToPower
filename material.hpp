#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <cstdlib>
#include <vector>

enum MATERIAL_TAGS {
	MAT_IS_WOOD = 1,
	MAT_IS_FIREPROOF = 2
};

// Contains the IDs to convert between tile, wall, and object
class Material {
public:
	std::vector<int> tileIDs;
	std::vector<std::string> wallIDs;
	std::string itemID;
	int tags;
	std::string name;
	int getRandomTileID();
	std::string getRandomWallID();
};

#endif