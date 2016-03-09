#ifndef UNIT_AI_HPP
#define UNIT_AI_HPP

#include "unit.hpp"
#include "map.hpp"
#include "a_star.hpp"
#include "job_queue.hpp"
#include "request_queue.hpp"

// Define some stuff to control unit movement behaviour
#define AI_MOVE_CENTER_OF_TILE
const float DISTANCE_FROM_CENTER = 3;
const float DISTANCE_FROM_CENTER_SQ = DISTANCE_FROM_CENTER * DISTANCE_FROM_CENTER;
const float UNIT_AI_UPDATE_TIME = 0.5;

enum JOB_STAGES {
	JOB_STAGE_NONE,
	JOB_STAGE_WALKING_TO_DEST,
	JOB_STAGE_ACTING
};

// Due to the way adding/removing AIs works, one should only assign ONE AI per Unit
class AI {
private:
	float timeSinceLastUpdate;
	void moveToNextPoint();
	bool isUnitCloseToCenterOfTile(point* unitLoc);
	int jobState;
	bool meetsJobRequirements(Job job);
	bool pickUpJob();
	void finishJob();
public:
	AI(Unit* controlled, Map* curMap);
	Unit* controlled;
	Map* curMap;
	Job curJob;
	point* lastKnownPos;
	std::string uid;
	void update(float dt);
};

#endif