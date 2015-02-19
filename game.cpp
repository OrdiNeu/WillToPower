#include "game.hpp"
using namespace std;

bool Game::init(){
	screen.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Will To Power");
	curMode = new ModeMapEdit();
	curMode->init();
	Mode::curMap = new Map();
	Mode::curMap->init(10,10);
	new Unit("./data/images/enemies/Slime.png", 5, 5);
	return true;
}

int Game::run(){
	if(init() == false)
		return EXIT_FAILURE;
	sf::Clock dtTimer;
	dtTimer.restart();
	float dt = 0;
	while(screen.isOpen()){
		screen.clear(sf::Color::Black);
		update(dt);
		render();
		screen.display();
		dt = dtTimer.restart().asSeconds();
	}
	return EXIT_SUCCESS;
}

void Game::update(float dt){
	curMode->update(dt, &screen);
}

void Game::render(){
	curMode->render(&screen);
}