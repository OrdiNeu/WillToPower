#include "game.hpp"
using namespace std;

Game::~Game(){
	delete Mode::entManager->unitManager;
	delete Mode::entManager->doodadManager;
	delete Mode::entManager;
	delete Mode::worldGen;
}

bool Game::init(){
	screen.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Will To Power");
	Mode::entManager = new EntityManager();
	Mode::entManager->unitManager = new UnitManager();
	Mode::entManager->doodadManager = new DoodadManager();
	Mode::worldGen = new WorldGenerator(Mode::entManager);
	Mode::curMap = Mode::worldGen->generateMap(0,0);
	Mode::entManager->unitManager->curMap = Mode::curMap;
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