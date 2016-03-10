#ifndef A_STAR_HPP
#define A_STAR_HPP

#include <cmath>
#include <iostream>
#include "map.hpp"

class AStarNode {
public:
	AStarNode(int x, int y, int target_x, int target_y, int g, AStarNode* parent);
	AStarNode* next;
	AStarNode* prev;
	AStarNode* parent;
	int getF();
	void insert(AStarNode* node);
	bool contains(int x, int y);
	int x, y;
	int g;
	float h;
};

// TODO: look up how to insert default arguments
std::vector<point*> AStarSearch(Map* map, int startx, int starty, int endx, int endy, float max_dist_to_accept = 0);

#endif