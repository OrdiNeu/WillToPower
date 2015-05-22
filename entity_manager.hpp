#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "entity.hpp"
#include "unit_manager.hpp"
#include "doodad_manager.hpp"
#include "request_queue.hpp"

enum ent_type {
	ENTITY_UNIT,
	ENTITY_DOODAD
};

class EntityManager {
public:
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addEnt(Entity* ent, int type);
	void removeEnt(std::string id, int type);
	UnitManager* unitManager;
	DoodadManager* doodadManager;
};

#endif