#include "a_star.hpp"

AStarNode::AStarNode(int x, int y, int target_x, int target_y, int g, AStarNode* parent) {
	this->x = x;
	this->y = y;
	this->g = g;
	int dx = (x-target_x);
	int dy = (y-target_y);
	h = sqrt(dx*dx + dy*dy);
	prev = parent;
	next = NULL;
}

// Get the F-cost of this node
int AStarNode::getF() {
	return g + h;
}

// Insert into this linked list in order of F
void AStarNode::insert(AStarNode* node) {
	// Check if the inserted node has a lower cost than this (root) node
	if (node->getF() < getF()) {
		// Copy that node's properties here, and this node's properties there
		// This is wildly unsafe (what if the inserted node is a child class?) but
		// this is under crunch time
		int oldx = x;
		int oldy = y;
		int oldg = g;
		int oldh = h;
		AStarNode* oldparent = parent;
		node->next = next;
		node->prev = this;
		x = node->x;
		y = node->y;
		g = node->g;
		h = node->h;
		parent = node->parent;
		next = node;
		node->x = oldx;
		node->y = oldy;
		node->g = oldg;
		node->h = oldh;
		node->parent = oldparent;
		return;
	}

	// Otherwise, mvoe down this list and see where to insert it
	AStarNode* prevNode = this;
	AStarNode* nextNode = next;
	while (nextNode) {
		// Does the inserted node have a lower F cost than the next one?
		if (node->getF() < nextNode->getF()) {
			nextNode->prev = node;
			node->next = nextNode;
			prevNode->next = node;
			node->prev = prevNode;
			return;
		}
		// Otherwise, move on to the next one
		prevNode = nextNode;
		nextNode = nextNode->next;
	}
	// End of chain: set it to the last node
	prevNode->next = node;
	node->prev = prevNode;
}

// Does this list contain the specified point?
bool AStarNode::contains(int x, int y) {
	if (this->x == x && this->y == y)
		return true;
	AStarNode* nextNode = next;
	while (nextNode) {
		if (nextNode->x == x && nextNode->y == y)
			return true;
		nextNode = nextNode->next;
	}
	return false;
}

// Please remember to delete the returned objects
// Returns a vector with no points if no path found, and a vector of points otherwise
std::vector<point*> AStarSearch(Map* map, int startx, int starty, int endx, int endy) {
	AStarNode* OpenList = new AStarNode(startx, starty, endx, endy, 0, NULL);
	AStarNode* ClosedList = new AStarNode(startx, starty, endx, endy, 0, NULL);
	std::vector<point*> retVal;
	AStarNode* thisNode = OpenList;
	while (OpenList) {
		int x = thisNode->x;
		int y = thisNode->y;

		// At the end?
		if (x == endx && y == endy) {
			// Populate the vector of points to nav through by looking through the parents
			while (thisNode) {
				point* thisPoint = new point;
				thisPoint->x = thisNode->x;
				thisPoint->y = thisNode->y;
				retVal.push_back(thisPoint);
				thisNode = thisNode->parent;
			}

			// Cleanup all of the node objects we've been initializing
			thisNode = OpenList;
			while (thisNode) {
				AStarNode* prevNode = thisNode;
				thisNode = thisNode->next;
				delete prevNode;
			}
			thisNode = ClosedList;
			while (thisNode) {
				AStarNode* prevNode = thisNode;
				thisNode = thisNode->next;
				delete prevNode;
			}

			return retVal;
		}

		// Search around the adjacent points
		// On a staggered isometric grid, this means that where you can move depends on whether or not y is odd
		// There's a speedup here if I used boolean math instead of branching, but it's unreadable: (x-1)+2*(y&1)
		int newy[] = {y+1, y-1,   y,   y};
		int* newx;
		if (y&1) {	// is y odd?
			newx = new int[4] {  x,   x, x+1, x+1};
		} else {
			newx = new int[4] {  x,   x, x-1, x-1};
		}
		for (int i = 0; i < 4; i++) {
			if ( map->inBounds(newx[i], newy[i])
					&& map->getTile(newx[i], newy[i])->tags & IS_WALKABLE
					&& !ClosedList->contains(newx[i], newy[i])
					&& !OpenList->contains(newx[i], newy[i]) ) {
				OpenList->insert(new AStarNode(newx[i], newy[i], endx, endy, thisNode->g + 1, thisNode));
			}
		}

		OpenList = OpenList->next;
		ClosedList->insert(OpenList);	// TODO: Speedup closed list by not having it be sorted
	}

	// No path found - cleanup
	thisNode = ClosedList;
	while (thisNode) {
		AStarNode* prevNode = thisNode;
		thisNode = thisNode->next;
		delete prevNode;
	}
	return retVal;
}