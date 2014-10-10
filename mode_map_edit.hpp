#ifndef MODE_MAP_EDIT
#define MODE_MAP_EDIT
#include "mode.hpp"
#include <SFML/Graphics.hpp>

class ModeMapEdit : public Mode {
public:
	void update(float dt);
	void render(sf::RenderTarget* screen);
};

#endif