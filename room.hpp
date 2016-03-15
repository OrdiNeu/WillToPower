#ifndef ROOM_HPP
#define ROOM_HPP
#include "doodad.hpp"

class Room {
	std::vector<int*> doodadIDsUsed;
	std::vector<Doodad*> doodadsAvailable;
};

#endif
