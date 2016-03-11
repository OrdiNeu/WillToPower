#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <regex>
#include <string>
#include "entity.hpp"
#include "unit_manager.hpp"
#include "doodad_manager.hpp"
#include "item_manager.hpp"
#include "request_queue.hpp"

class EntityManager {
private:
	std::vector<Entity*> ents;
	void addToEntList(Entity* ent);
public:
	void render(sf::RenderTarget* screen);
	void update(float dt);
	void addEnt(Entity* ent, int type);
	void removeEnt(std::string uid, int type);
	void flushRequests();
	Entity* addNewEntByType(std::string name, int type, float x, float y);
	UnitManager* unitManager;
	DoodadManager* doodadManager;
	ItemManager* itemManager;
};

#endif