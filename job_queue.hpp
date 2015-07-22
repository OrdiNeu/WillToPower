#ifndef JOB_QUEUE_HPP
#define JOB_QUEUE_HPP

#include <vector>
#include "constants.hpp"
#include "entity.hpp"

const int NUM_SKILLS = 1;

enum SKILLS {
	SKILL_MINING = 0
};

enum JOB_TYPES {
	JOB_TYPE_MINING = 0
};

struct Job {
	int requirements;
	int type;
	bool suspended;
	bool repeating;
	Entity* targetEnt;
	point*  targetPoint;
	Entity* assigned;
};

// The job queue is like a billboard of jobs that units can pick up and complete when their AI runs out of things to do
class JobQueue {
public:
	static std::vector<Job> jobQueue;
};

#endif