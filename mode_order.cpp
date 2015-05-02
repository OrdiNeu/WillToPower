#include "mode_order.hpp"
using namespace std;

ModeOrder::ModeOrder() {
}

void ModeOrder::init() {
	test = new Unit("./data/images/enemies/yellowBox.png", 25, 15);
	Mode::unitManager->addUnit(test);

	// Force the user to let go of either button before acknowledging a click
	leftClicked = true;
	rightClicked = true;
}

void ModeOrder::update(float dt, sf::RenderWindow* screen) {
	sf::Event e;
	while(screen->pollEvent(e)){
		if(e.type == sf::Event::Closed){
			screen->close();
		}
	}
	unitManager->update(dt);

	if (!leftClicked && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		leftClicked = true;
		sf::Vector2i mousePos = sf::Mouse::getPosition(*screen);
		point* clicked = Map::TexXYToTileXY(mousePos.x, mousePos.y);
		Job thisJob;
		thisJob.requirements = SKILL_MINING;
		thisJob.suspended = false;
		thisJob.repeating = false;
		thisJob.targetPoint = clicked;
		thisJob.type = JOB_TYPE_MINING;
		JobQueue::jobQueue.push_back(thisJob);
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		leftClicked = false;
	}

	if (!rightClicked && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		rightClicked = true;
		sf::Vector2i mousePos = sf::Mouse::getPosition(*screen);
		point* clicked = Map::TexXYToTileXY(mousePos.x, mousePos.y);
		std::vector<point*> route = AStarSearch(curMap, test->tileX, test->tileY, clicked->tileX, clicked->tileY);
		delete clicked;

		if (route.size() != 0) {
			// Remove the last point in the route, since it is the current position
			point* last_point = route.back();
			delete last_point;
			route.pop_back();

			// Walk to the target location
			test->walkTo(route);
			std::cout << "Test unit at (" << test->tileX << "," << test->tileY << ") (" << test->realX << "," << test->realY << ") is moving to (" << \
						 route.back()->tileX << "," << route.back()->tileY << ") (" << route.back()->realX << "," << route.back()->realY << ")" << std::endl;
		}
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		rightClicked = false;
	}
}

void ModeOrder::render(sf::RenderTarget* screen) {
	curMap->render(screen);
	unitManager->render(screen);
}