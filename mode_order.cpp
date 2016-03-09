#include "mode_order.hpp"
using namespace std;

float MAP_SCROLL_SPEED = 300;

ModeOrder::ModeOrder() {
}

void ModeOrder::init() {
	Unit testUnit = Unit("test","./data/images/enemies/yellowBox.png",0,0);
	testUnit.skills = SKILL_MINING | SKILL_WOODCUT;
	entManager->unitManager->addNewEntType("testUnit",testUnit);
	RequestQueues::entityRequests.push_back(entRequest::newEntRequest("testUnit", HALF_TILE_WIDTH, HALF_TILE_HEIGHT, ENT_TYPE_UNIT));
	entManager->flushRequests();
	test = entManager->unitManager->lastCreatedEnt;

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
	thisJob.assigned = NULL;
	thisJob.targetEnt = targetEnt;//NULL;
	thisJob.targetPoint = targetPoint;//clicked;
	thisJob.type = type;//JOB_TYPE_MINING;
	JobQueue::jobQueue.push_back(thisJob);
}

// Rearranges x0 and x1, if necessary
void ModeOrder::checkBounds(int* x0, int* x1) {
	if (*x0 > *x1) {
		int xtemp = *x0;
		*x0 = *x1;
		*x1 = xtemp;
	}
}

void ModeOrder::findTasksInArea(int type, int x0, int x1, int y0, int y1, bool doCreateJob, bool colorize, bool uncolorize) {
	checkBounds(&x0, &x1);
	checkBounds(&y0, &y1);

	for (int y = y0; y <= y1; y++) {
		int staggerFix = y%2-y0%2;	// To only grab the tiles that are "inner", we need to account for tiles that are odd "sticking out"
		for (int x = x0; x <= x1 - staggerFix; x++) {
			switch (type) {
				case JOB_TYPE_MINING:
				{
					// Mining jobs: any tile with the IS_MINABLE tag is assigned a mining job
					if (curMap->inBounds(x,y) && curMap->getTile(x,y)->hasTag(IS_MINABLE)) {
						if (doCreateJob) {
							point* thisSpot = Map::TileXYToTexXY(x, y);
							createJob(JOB_TYPE_MINING, SKILL_MINING, NULL, thisSpot);
							curMap->setTasked(x,y,true);
							// Don't delete this point
						}

						// need to rethink this: where should the color for a tile actually be determined? In map?
						if (colorize) curMap->setColor(x, y, COLOR_TASKED);
						if (uncolorize && !curMap->getTasked(x,y)) curMap->setColor(x, y, COLOR_NONE);
					}
					break;
				}
				case JOB_TYPE_WOODCUT:
				{
					// Woodcutting jobs: any doodad with the IS_TREE tag is assigned a mining job
					std::vector<Doodad*> doodadsHere = entManager->doodadManager->getDoodadsAtPoint(x,y);
					for (Doodad* thisDoodad : doodadsHere) {
						if (thisDoodad->hasTag(IS_TREE)) {
							if (doCreateJob) createJob(JOB_TYPE_WOODCUT, SKILL_WOODCUT, thisDoodad, NULL);
							if (colorize) thisDoodad->spr.setColor(DEFAULT_TILE_COLORS[COLOR_TASKED]);
							if (uncolorize) thisDoodad->spr.setColor(DEFAULT_TILE_COLORS[COLOR_NONE]);
						}
					}
					break;
				}
				default:
				{
					cerr << "Unknown jobtype in findTasksInArea: " << type << endl;
					break;
				}
			}
		}
	}
}

sf::Vector2i ModeOrder::getMousePos(sf::RenderWindow* screen) {
	return sf::Mouse::getPosition(*screen) + sf::Vector2i(screenX,screenY);
}

void ModeOrder::handleKeyboard(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		screenX -= MAP_SCROLL_SPEED*dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		screenX += MAP_SCROLL_SPEED*dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		screenY -= MAP_SCROLL_SPEED*dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		screenY += MAP_SCROLL_SPEED*dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		setOrderMode(ORDER_MODE_DIG);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		setOrderMode(ORDER_MODE_CUTTREE);
	}
};

void ModeOrder::handleMouse(sf::RenderWindow* screen) {
	sf::Vector2i mousePos = getMousePos(screen);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!leftClicked && selectionActive == SELECT_TYPE_NONE) { // Initiate clicking
			selectionActive = SELECT_TYPE_LEFT;
			point* startPoint = Map::TexXYToTileXY(mousePos.x, mousePos.y);
			selectStartX = startPoint->tileX;
			selectStartY = startPoint->tileY;
			leftClicked = true;
			delete startPoint;
		} else if (selectionActive == SELECT_TYPE_LEFT) {
			point* thisPoint = Map::TexXYToTileXY(mousePos.x, mousePos.y);
			if (thisPoint->tileX != selectLastX || thisPoint->tileY != selectLastY) {
				// redraw
				if (curOrderType == ORDER_MODE_DIG) {
					findTasksInArea(JOB_TYPE_MINING, selectStartX, selectLastX, selectStartY, selectLastY, false, false, true);
					findTasksInArea(JOB_TYPE_MINING, selectStartX, thisPoint->tileX, selectStartY, thisPoint->tileY, false, true, false);
				} else if (curOrderType == ORDER_MODE_CUTTREE) {
					findTasksInArea(JOB_TYPE_WOODCUT, selectStartX, selectLastX, selectStartY, selectLastY, false, false, true);
					findTasksInArea(JOB_TYPE_WOODCUT, selectStartX, thisPoint->tileX, selectStartY, thisPoint->tileY, false, true, false);
				}
				selectLastX = thisPoint->tileX;
				selectLastY = thisPoint->tileY;
			}
			delete thisPoint;
		}
	} else {
		if (leftClicked && selectionActive == SELECT_TYPE_LEFT) {
			selectionActive = SELECT_TYPE_NONE;
			point* endPoint = Map::TexXYToTileXY(mousePos.x, mousePos.y);
			if (curOrderType == ORDER_MODE_DIG) {
				findTasksInArea(JOB_TYPE_MINING, selectStartX, endPoint->tileX, selectStartY, endPoint->tileY, true, true, false);
			} else if (curOrderType == ORDER_MODE_CUTTREE) {
				findTasksInArea(JOB_TYPE_WOODCUT, selectStartX, endPoint->tileX, selectStartY, endPoint->tileY, true, true, false);
			}
		}
		leftClicked = false;
	}

	if (!rightClicked && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		selectionActive = SELECT_TYPE_RIGHT;
		rightClicked = true;
		point* clicked = Map::TexXYToTileXY(mousePos.x, mousePos.y);
		point* unitPoint = Map::TexXYToTileXY(test->realX, test->realY);
		std::vector<point*> route = AStarSearch(curMap, unitPoint->tileX, unitPoint->tileY, clicked->tileX, clicked->tileY);
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
};

void ModeOrder::update(float dt, sf::RenderWindow* screen) {
	sf::Event e;
	while(screen->pollEvent(e)){
		if(e.type == sf::Event::Closed){
			screen->close();
		}
	}
	entManager->update(dt);

	handleKeyboard(dt);
	handleMouse(screen);
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
	selectionTex.display();	// Update the texture
	selectionSprite.setTexture(selectionTex.getTexture());
}