#ifndef MODE
#define MODE
#include "map.hpp"
#include "unit_manager.hpp"
#include <SFML/Graphics.hpp>

class Mode {
	friend class Game;
protected:
	// Static pointers to things shared between all modes
	static Map* curMap;
	static UnitManager* unitManager;
public:
	virtual void init();
	virtual void update(float dt, sf::RenderWindow* screen){};
	virtual void render(sf::RenderTarget* screen){};
};

#endif