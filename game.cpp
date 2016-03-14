#include "game.hpp"
using namespace std;

Game::~Game(){
	delete Mode::entManager->unitManager;
	delete Mode::entManager->doodadManager;
	delete Mode::entManager;
	delete Mode::worldGen;
}

bool Game::init(){
	screen.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Will To Power: 0 FPS");
	Mode::entManager = new EntityManager();
	Mode::entManager->unitManager = new UnitManager();
	Mode::entManager->doodadManager = new DoodadManager();
	Mode::entManager->itemManager = new ItemManager();
	XmlLoader::loadUnits(Mode::entManager->unitManager,"./data/units.xml");
	Mode::worldGen = new WorldGenerator(Mode::entManager,0);
	Mode::curMap = Mode::worldGen->getMap(0,0);
	Mode::entManager->unitManager->curMap = Mode::curMap;
	curMode = new ModeOrder();
	curMode->init();
	return true;
}

int Game::run(){
	/*try {
		init();
	}
	catch (exception e) {
		std::cout << e.id << std::endl;
		return EXIT_FAILURE;
	}*/
	if(init() == false)
		return EXIT_FAILURE;
	sf::Clock dtTimer;
	dtTimer.restart();
	float dt = 0;
	const float RENDER_DELAY = 1.0 / MAX_FPS;
	float time_to_next_second = 1;
	float time_to_render = RENDER_DELAY;
	int frames_rendered = 0;
	int updates = 0;
	while(screen.isOpen()){
		dt = dtTimer.restart().asSeconds();
		time_to_next_second -= dt;
		time_to_render -= dt;
		updates++;
		update(dt);
		if (frames_rendered < MAX_FPS && time_to_render < 0) {
			time_to_render = RENDER_DELAY;
			screen.clear(sf::Color::Black);
			render();
			screen.display();
			frames_rendered++;
		}
		if (time_to_next_second < 0) {
			time_to_next_second = 1;
			char title[60];
			snprintf(title, 60, "Will To Power: %i FPS, %i updates",frames_rendered,updates);
			screen.setTitle(title);
			frames_rendered = 0;
			updates = 0;
		}
	}
	return EXIT_SUCCESS;
}

void Game::update(float dt){
	curMode->update(dt, &screen);
}

void Game::render(){
	curMode->render(&screen);
}