#include "mode_order.hpp"
using namespace std;

int MAP_SCROLL_SPEED = 1;

ModeOrder::ModeOrder() {
}

void ModeOrder::init() {
	Unit testUnit = Unit("test","./data/images/enemies/yellowBox.png");
	testUnit.skills = SKILL_MINING;
	entManager->unitManager->addNewUnitType("testUnit",testUnit);
	RequestQueues::entityRequests.push_back(entRequest::newUnitRequest("testUnit", HALF_TILE_WIDTH, HALF_TILE_HEIGHT));
	entManager->flushRequests();
	test = entManager->unitManager->lastCreatedUnit;

	leftClicked = true;
	rightClicked = true;
	screenX = 0;
	screenY = 0;
	selectionActive = SELECT_TYPE_NONE;
	curOrderType = ORDER_MODE_DIG;
}

void ModeOrder::setOrderMode(int orderType) {
	curOrderType = orderType;
}

void ModeOrder::createJob(int type, int requirements, Entity* targetEnt, point* targetPoint) {
	Job thisJob;
	thisJob.requirements = requirements;//SKILL_MINING;
	thisJob.suspended = false;
	thisJob.repeating = false;
	thisJob.targetEnt = targetEnt;//NULL;
	thisJob.targetPoint = targetPoint;//clicked;
	thisJob.type = type;//JOB_TYPE_MINING;
	JobQueue::jobQueue.push_back(thisJob);
}

void ModeOrder::createJobsInArea(int type, int x0, int x1, int y0, int y1) {
	// rearrange x0/y0 if necessary
	if (x0 > x1) {
		int xtemp = x0;
		x0 = x1;
		x1 = xtemp;
	}
	if (y0 > y1) {
		int ytemp = y0;
		y0 = y1;
		y1 = ytemp;
	}

	// What we do next depends on the type of job assiged
	switch (type) {
		case JOB_TYPE_MINING:
			// Mining jobs: any minable tile is assigned a mining job
			for (int x = x0; x <= x1; x++) {
				for (int y = y0; y <= y1; y++) {
					if (curMap->inBounds(x,y) && (curMap->getTile(x,y)->tags & IS_MINABLE) > 0) {
						point* thisSpot = Map::TileXYToTexXY(x, y);
						createJob(JOB_TYPE_MINING, SKILL_MINING, NULL, thisSpot);
					}
				}
			}
		break;
		case JOB_TYPE_WOODCUT:
			// Woodcutting jobs: any doodad with the IS_TREE tag is assigned a mining job
			for (int x = x0; x <= x1; x++) {
				for (int y = y0; y <= y1; y++) {
					std::vector<Doodad*> doodadsHere = entManager->doodadManager->getDoodadsAtPoint(x,y);
					for (Doodad* thisDoodad : doodadsHere) {
						if (thisDoodad->tags & IS_TREE) {
							createJob(JOB_TYPE_WOODCUT, SKILL_WOODCUT, thisDoodad, NULL);
						}
					}
				}
			}
		break;
		default:
			cerr << "Unknown jobtype in createJobsInArea: " << type << endl;
		break;
	}
}

sf::Vector2i ModeOrder::getMousePos(sf::RenderWindow* screen) {
	return sf::Mouse::getPosition(*screen) - sf::Vector2i(screenX,screenY);
}

void ModeOrder::update(float dt, sf::RenderWindow* screen) {
	sf::Event e;
	while(screen->pollEvent(e)){
		if(e.type == sf::Event::Closed){
			screen->close();
		}
	}
	entManager->update(dt);

	// Keyboard controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		screenX -= MAP_SCROLL_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		screenX += MAP_SCROLL_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		screenY -= MAP_SCROLL_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		screenY += MAP_SCROLL_SPEED;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		setOrderMode(ORDER_MODE_DIG);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		setOrderMode(ORDER_MODE_CUTTREE);
	}

	// Mouse controls
	sf::Vector2i mousePos = getMousePos(screen);
	if (!leftClicked && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (selectionActive == SELECT_TYPE_NONE) {
			selectionActive = SELECT_TYPE_LEFT;
			point* startPoint = Map::TexXYToTileXY(mousePos.x, mousePos.y);
			selectStartX = startPoint->tileX;
			selectStartY = startPoint->tileY;
			leftClicked = true;
		}
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (leftClicked && selectionActive == SELECT_TYPE_LEFT) {
			selectionActive = SELECT_TYPE_NONE;
			point* endPoint = Map::TexXYToTileXY(mousePos.x, mousePos.y);
			if (curOrderType == ORDER_MODE_DIG) {
				createJobsInArea(JOB_TYPE_MINING, selectStartX, endPoint->tileX, selectStartY, endPoint->tileY);
			} else if (curOrderType == ORDER_MODE_CUTTREE) {
				createJobsInArea(JOB_TYPE_WOODCUT, selectStartX, endPoint->tileX, selectStartY, endPoint->tileY);
			}
			cout << "Worked: " << JobQueue::jobQueue.size() << endl;
		}
		leftClicked = false;
	}

	if (!rightClicked && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		selectionActive = SELECT_TYPE_RIGHT;
		rightClicked = true;
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
		}
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (rightClicked)
			selectionActive = SELECT_TYPE_NONE;
		rightClicked = false;
	}
}

void ModeOrder::render(sf::RenderTarget* screen) {
	sf::Vector2u size = screen->getSize();
	sf::View view = screen->getView();
	view.setCenter(screenX+float(size.x)/2, screenY+float(size.y)/2);
	screen->setView(view);
	curMap->render(screen);
	entManager->render(screen);
}

void ModeOrder::rerenderSelection(sf::RenderWindow* screen) {
	selectionTex.clear();
	if (selectionActive > 0) {
		/*sf::Vector2i mousePos = getMousePos(screen);
		point* point1 = Map::TexXYToTileXY(mousePos.x, mousePos.y);
		int x0 = (point1->tileX < selectStartX) ? point1->tileX : selectStartX;
		int x1 = (point1->tileX < selectStartX) ? selectStartX : point1->tileX;
		int y0 = (point1->tileY < selectStartY) ? point1->tileY : selectStartY;
		int y1 = (point1->tileY < selectStartY) ? selectStartY : point1->tileY;
		for (int x = x0; x <= x1; x++) {
			for (int y = y0; y <= y1; y++) {
				// Draw the thingymobob

			}
		}*/
	}
	selectionTex.display();	// Update the texture
	selectionSprite.setTexture(selectionTex.getTexture());
}
