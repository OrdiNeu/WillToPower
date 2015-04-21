#include "mode_order.hpp"
using namespace std;

ModeOrder::ModeOrder() {
}

void ModeOrder::init() {
	test = new Unit("./data/images/enemies/yellowBox.png", 25, 15);
	Mode::unitManager->addUnit(test);
}

void ModeOrder::update(float dt, sf::RenderWindow* screen) {
	sf::Event e;
	while(screen->pollEvent(e)){
		if(e.type == sf::Event::Closed){
			screen->close();
		}
	}
	unitManager->update(dt);

	if (!rightClicked && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		rightClicked = true;
		std::vector<point*> route = AStarSearch(curMap, test->tileX, test->tileY, curMap->width-1, curMap->height-1);

		// Remove the last point in the route, since it is the current position
		point* last_point = route.back();
		delete last_point;
		route.pop_back();

		// Walk to the target location
		test->walkTo(route);
		std::cout << "Test unit at (" << test->tileX << "," << test->tileY << ") (" << test->realX << "," << test->realY << ") is moving to (" << \
					 route.back()->tileX << "," << route.back()->tileY << ") (" << route.back()->realX << "," << route.back()->realY << ")" << std::endl;
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		rightClicked = false;
	}
}

void ModeOrder::render(sf::RenderTarget* screen) {
	curMap->render(screen);
	unitManager->render(screen);
}