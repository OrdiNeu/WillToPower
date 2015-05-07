#include "mode_main_menu.hpp"
using namespace std;

ModeMainMenu::ModeMainMenu() {
}

void ModeMainMenu::init() {
	
}

void ModeMainMenu::update(float dt, sf::RenderWindow* screen) {
	sf::Event e;
	while(screen->pollEvent(e)){
		if(e.type == sf::Event::Closed){
			screen->close();
		}
	}
}

void ModeMainMenu::render(sf::RenderTarget* screen) {
	curMap->render(screen);
	for (Unit* u : entManager->unitManager->units) {
		u->render(screen);
	}
}