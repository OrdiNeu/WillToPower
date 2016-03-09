#include "manager.hpp"
/*
template <class T>
T* Manager<T>::addNewEntByType(std::string type) {
	// Ensure that the type exists
	if (ent_library.find(type) == ent_library.end()) {
		std::cerr << "ERROR: attempted to create unit of unknown type " << type << std::endl;
		return NULL;
	}

	// Construct a name for the ent
	std::ostringstream stream;
	stream << type << "_" << num_ents_created[type]++;

	T* newEnt = ent_library[type].clone(stream.str());
	lastCreatedEnt = newEnt;
	return newEnt;
}

template <class T>
void Manager<T>::addNewEntType(std::string type, T newEnt) {
	ent_library[type] = newEnt;
}

template <class T>
void Manager<T>::addEnt(T* ent) {
	ents.push_back(ent);
}

template <class T>
void Manager<T>::removeEnt(std::string uid) {
	// Find the entity and do an in-place swap with the final element, then shrink
	for (std::vector<T*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
		if ((*it)->uid == uid) {
			*it = ents[ents.size()-1];
			ents.pop_back();
		}
	}
}

template <class T>
void Manager<T>::render(sf::RenderTarget* screen) {
	for (T* thisEnt : ents) {
		thisEnt->render(screen);
	}
};

template <class T>
void Manager<T>::update(float dt) {
	for (T* thisEnt : ents) {
		thisEnt->update(dt);
	}
};*/