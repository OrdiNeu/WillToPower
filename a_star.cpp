#include "a_star.hpp"
using namespace std;

AStarNode::AStarNode(int x, int y, int target_x, int target_y, int g, AStarNode* parent) : x(x) {
	this->y = y;
	this->g = g;
	int dx = (x-target_x);
	int dy = (y-target_y);
	h = sqrt(dx*dx + float(dy*dy)/4);
	this->parent = parent;
	prev = NULL;
	next = NULL;
}

// Get the F-cost of this node
int AStarNode::getF() {
	return g + h;
}

// Insert into this linked list in order of F
// This will NOT replace this (root) node
void AStarNode::insert(AStarNode* node) {
	// Move down this list and see where to insert it
	AStarNode* prevNode = this;
	AStarNode* nextNode = next;
	//cout << "Insertion: " << x << ',' << y << " -> ";
	while (nextNode) {
		// Does the inserted node have a lower F cost than the next one?
		//cout << nextNode->x << ',' << nextNode->y << " -> ";
		if (node->getF() < nextNode->getF()) {
			nextNode->prev = node;
			node->next = nextNode;
			prevNode->next = node;
			node->prev = prevNode;
			//cout << "Insertion: " << prevNode->x << "," << prevNode->y << " -> " << node->x << "," << node->y << " -> " << nextNode->x << "," << nextNode->y << endl;
			//cout << node->x << ',' << node->y << " -> ";
			while (nextNode) {
				//cout << nextNode->x << ',' << nextNode->y << " -> ";
				nextNode = nextNode->next;
			}
			//cout << endl;
			return;
		}
		// Otherwise, move on to the next one
		prevNode = nextNode;
		nextNode = nextNode->next;
	}
	// End of chain: set it to the last node
	//cout << node->x << ',' << node->y << endl;
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
std::vector<point> AStarSearch(Map* map, int startx, int starty, int endx, int endy, float max_dist_to_accept) {
	AStarNode* OpenList = new AStarNode(startx, starty, endx, endy, 0, NULL);
	AStarNode* ClosedList = new AStarNode(startx, starty, endx, endy, 0, NULL);
	std::vector<point> retVal;
	AStarNode* thisNode;
	if (map->inBounds(endx, endy) && map->inBounds(startx, starty)) {
		while (OpenList) {
			thisNode = OpenList;
			int x = thisNode->x;
			int y = thisNode->y;
			//cout << "Now evaluating (" << x << "," << y << ")" << endl;

			// At the end?
			if (thisNode->h <= max_dist_to_accept) {
				//cout << x << "," << y << " to " << endx << "," << endy << " is " << thisNode->h << endl;
				//cout << "Finished at (" << x << "," << y << ")" << endl;
				// Populate the vector of points to nav through by looking through the parents
				while (thisNode) {
					retVal.push_back(Map::TileXYToTexXY(thisNode->x, thisNode->y));
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

			int newy[] = {y+1, y+1, y-1, y-1};
			int* newx;
			if (y&1) {	// is y odd?
				newx = new int[4] {x, x+1, x+1, x};
			} else {
				newx = new int[4] {x-1, x, x, x-1};
			}

			// Search around the adjacent points
			// On a staggered isometric grid, this means that where you can move depends on whether or not y is odd
			// There's a speedup here if I used boolean math instead of branching, but it's unreadable: (x-1)+2*(y&1)
			for (int i = 0; i < 4; i++) {
				//cout << "\tadding (" << newx[i] << "," << newy[i] << ")" << endl;
				if ( (map->isWalkable(newx[i], newy[i])/* || ( newx[i] == endx && newy[i] == endy )*/)
						&& !ClosedList->contains(newx[i], newy[i])
						&& !OpenList->contains(newx[i], newy[i]) ) {
					//cout << "\t(" << x << "," << y << ")" << " added (" << newx[i] << "," << newy[i] << ")" << endl;
					OpenList->insert(new AStarNode(newx[i], newy[i], endx, endy, thisNode->g + 1, thisNode));
				}
			}

			// Handle moving directly up, down, left, and right. In order to move in one of these directions,
			// BOTH of the diagonal directions AND the target direction must be free to move in.
			int diagonal_x[] = {x, x+1, x, x-1};
			int diagonal_y[] = {y+2, y, y-2, y};
			for (int i = 0; i < 4; i++) {
				int j = (i+1)%4;	// The other direction being checked
				int thisx = diagonal_x[i];
				int thisy = diagonal_y[i];
				if ( ((map->isWalkable(newx[i], newy[i])
						&& map->isWalkable(newx[j], newy[j])
						&& map->isWalkable(thisx, thisy))  /*|| ( thisx == endx && thisy == endy )*/)
						&& !ClosedList->contains(thisx, thisy)
						&& !OpenList->contains(thisx, thisy) ) {
					OpenList->insert(new AStarNode(thisx, thisy, endx, endy, thisNode->g + 1, thisNode));
				}
			}

			//cout << "endInsert: ";
			OpenList = OpenList->next;
			thisNode->next = NULL;
			ClosedList->insert(thisNode);	// TODO: Speedup closed list by not having it be sorted
		}
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