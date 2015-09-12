#include "game.hpp"
using namespace std;

bool Game::init(){
	screen.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Will To Power");
	Mode::entManager = new EntityManager();
	Mode::entManager->unitManager = new UnitManager();
	Mode::entManager->doodadManager = new DoodadManager();
	Mode::curMap = new Map();
	Mode::entManager->unitManager->curMap = Mode::curMap;
	Mode::curMap->init(10,10);
	curMode = new ModeOrder();
	curMode->init();
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