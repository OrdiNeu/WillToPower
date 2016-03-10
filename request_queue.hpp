#ifndef REQUEST_QUEUE_HPP
#define REQUEST_QUEUE_HPP

#include <string>
#include <vector>

enum entRequestTypes {
	ENT_REQUEST_NEW_ENT = 1,
	ENT_REQUEST_DEL_ENT = 2
};

enum entTypes {
	ENT_TYPE_UNIT = 1,
	ENT_TYPE_DOODAD = 2,
	ENT_TYPE_ITEM = 3,
	ENT_TYPE_COUNT = 3
};

class entRequest {
public:
	int entRequestType;
	int entType;
	std::string entName;
	std::string uid;
	int X;
	int Y;
	static entRequest newEntRequest(std::string ent_name, int X, int Y, int ent_type) {
		entRequest thisRequest;
		thisRequest.entName = ent_name;
		thisRequest.X = X;
		thisRequest.Y = Y;
		thisRequest.entRequestType = ENT_REQUEST_NEW_ENT;
		thisRequest.entType = ent_type;
		return thisRequest;
	};
	static entRequest delEntRequest(std::string uid, int ent_type) {
		entRequest thisRequest;
		thisRequest.uid = uid;
		thisRequest.entRequestType = ENT_REQUEST_DEL_ENT;
		thisRequest.entType = ent_type;
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