#ifndef REQUEST_QUEUE_HPP
#define REQUEST_QUEUE_HPP

#include <string>
#include <vector>

enum entRequestTypes {
	ENT_REQUEST_NEW_UNIT,
	ENT_REQUEST_DEL_UNIT
};

class entRequest {
public:
	int entRequestType;
	std::string unitName;
	std::string unitID;
	int X;
	int Y;
	static entRequest newUnitRequest(std::string UnitName, int X, int Y) {
		entRequest thisRequest;
		thisRequest.unitName = UnitName;
		thisRequest.X = X;
		thisRequest.Y = Y;
		thisRequest.entRequestType = ENT_REQUEST_NEW_UNIT;
		return thisRequest;
	};
	static entRequest delUnitRequest(std::string UnitID) {
		entRequest thisRequest;
		thisRequest.unitID = UnitID;
		thisRequest.entRequestType = ENT_REQUEST_DEL_UNIT;
		return thisRequest;
	};
private:
	entRequest() {};
};

// The request queue is a queue of things that we want the entity manager, current map, etc. to do.
// e..g. making new units, changing the walkability of tiles, etc.
class RequestQueues {
public:
	static std::vector<entRequest> entityRequests;
	//static std::vector<mapRequest> mapRequests;
};


#endif