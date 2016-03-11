#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <vector>
#include "map.hpp"

template <typename T>
class Manager {
protected:
	std::unordered_map<std::string, T> ent_library;
	std::vector<T*> ents;
public:
	std::unordered_map<std::string, int> num_ents_created;
	T* lastCreatedEnt;
	Map* curMap;

	virtual ~Manager() {}

	/*
	 * Moved to entity_manager
	virtual void render(sf::RenderTarget* screen) {
		for (T* thisEnt : ents) {
			thisEnt->render(screen);
		}
	};*/

	virtual void update(float dt) {
		for (T* thisEnt : ents) {
			thisEnt->update(dt);
		}
	};

	virtual T* addNewEntByType(std::string type) {
		// Ensure that the type exists
		if (ent_library.find(type) == ent_library.end()) {
			std::cerr << "ERROR: attempted to create entity of unknown type " << type << std::endl;
			return NULL;
		}

		// Construct a name for the ent
		std::ostringstream stream;
		stream << type << "_" << num_ents_created[type]++;

		T* newEnt = ent_library[type].clone(stream.str());
		lastCreatedEnt = newEnt;
		addEnt(newEnt);
		return newEnt;
	};

	virtual void addNewEntType(std::string type, T newEnt) {
		ent_library[type] = newEnt;
	};

	virtual T* removeEnt(std::string uid) {
		// Find the entity and do an in-place swap with the final element, then shrink
		for (typename std::vector<T*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
			if ((*it)->uid == uid) {
				T* removedUnit = *it;
				*it = ents[ents.size()-1];
				ents.pop_back();
				return removedUnit;
			}
		}
		return NULL;
	};

	virtual void addEnt(T* ent) {
		ents.push_back(ent);
	};
};

#endif