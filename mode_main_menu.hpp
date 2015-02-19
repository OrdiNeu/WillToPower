#ifndef MODE_MAIN_MENU
#define MODE_MAIN_MENU
#include "mode.hpp"
#include "constants.hpp"
#include "unit.hpp"
#include <SFML/Graphics.hpp>

class ModeMainMenu : public Mode {
private:
public:
	ModeMainMenu();
	void init();
	void update(float dt, sf::RenderWindow* screen);
	void render(sf::RenderTarget* screen);
};

#endif