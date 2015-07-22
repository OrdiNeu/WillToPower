#ifndef REQUEST_QUEUE_HPP
#define REQUEST_QUEUE_HPP

#include <string>
#include <vector>

const char NEW_UNIT_REQUEST_HEADER[] = "NEWUNIT:";	// Followed by the unit type id
const char DEL_UNIT_REQUEST_HEADER[] = "DELUNIT:";	// Followed by the unit handle id

// The request queue is a queue of things that we want the entity manager, current map, etc. to do.
// e..g. making new units, changing the walkability of tiles, etc.
class RequestQueues {
public:
	static std::vector<std::string> entityRequests;
	static std::vector<std::string> mapRequests;
};

#endif