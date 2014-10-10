#include "game.hpp"
using namespace std;

bool Game::init(){
	screen.create(sf::VideoMode(800,600), "Will To Power");
	cout <<"GameInit"<<endl;
	curMap.init(1,1);
	return true;
}

int Game::run(){
	if(init() == false)
		return EXIT_FAILURE;
	sf::Event e;
	sf::Clock dtTimer;
	dtTimer.restart();
	float dt = 0;
	while(screen.isOpen()){
		while(screen.pollEvent(e)){
			if(e.type == sf::Event::Closed){
				screen.close();
			}
		}
		screen.clear(sf::Color::Black);
		update(dt);
		render();
		screen.display();
		dt = dtTimer.restart().asSeconds();
	}
	return EXIT_SUCCESS;
}

void Game::update(float dt){
	curMap.update(dt);
}

void Game::render(){
	curMap.render(screen);
}