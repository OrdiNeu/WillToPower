#ifndef MODE_ORDER
#define MODE_ORDER
#include "mode.hpp"
#include "constants.hpp"
#include "unit_manager.hpp"
#include <SFML/Graphics.hpp>

class ModeOrder : public Mode {
private:
	bool rightClicked;
	Unit* test;
public:
	ModeOrder();
	void init();
	void update(float dt, sf::RenderWindow* screen);
	void render(sf::RenderTarget* screen);
};

#endif