#ifndef MODE_HPP
#define MODE_HPP
#include "map.hpp"
#include "entity_manager.hpp"
#include "world_generator.hpp"
#include <SFML/Graphics.hpp>

class Mode {
	friend class Game;
protected:
	// Static pointers to things shared between all modes
	static Map* curMap;
	static EntityManager* entManager;
	static WorldGenerator* worldGen;
public:
	virtual void init();
	virtual void update(float dt, sf::RenderWindow* screen){};
	virtual void render(sf::RenderTarget* screen){};
};

#endif