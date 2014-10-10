#ifndef MODE
#define MODE
#include "map.hpp"
#include <SFML/Graphics.hpp>

class Mode {
	friend class Game;
protected:
	// Static pointers to things shared between all modes
	static Map* curMap;
public:
	static void init();
	virtual void update(float dt){};
	virtual void render(sf::RenderTarget* screen){};
};

#endif