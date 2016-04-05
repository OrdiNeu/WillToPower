#include "mode_order.hpp"
using namespace std;

float MAP_SCROLL_SPEED = 300;

ModeOrder::ModeOrder() {
}

void ModeOrder::init() {
	RequestQueues::entityRequests.push_back(entRequest::newEntRequest("testUnit", HALF_TILE_WIDTH, HALF_TILE_HEIGHT, ENT_TYPE_UNIT));
	entManager->flushRequests();
	test = entManager->unitManager->lastCreatedEnt;
	test->skills = SKILL_MINING | SKILL_WOODCUT;

	leftClicked = true;
	rightClicked = true;
	screenX = 0;
	screenY = 0;
	selectionActive = SELECT_TYPE_NONE;
	curOrderType = ORDER_MODE_DIG;

	digButton = new UIDrawable("./data/images/skills/BoostAtk.png", -WINDOW_WIDTH/2, WINDOW_HEIGHT/2-40);
	woodcutButton = new UIDrawable("./data/images/skills/VoltIcon.png", -WINDOW_WIDTH/2+40, WINDOW_HEIGHT/2-40);
	buildButton = new UIDrawable("./data/images/skills/HealIcon.png", -WINDOW_WIDTH/2+80, WINDOW_HEIGHT/2-40);
}

void ModeOrder::setOrderMode(int orderType) {
	curOrderType = orderType;
}

void ModeOrder::createJob(int type, int requirements, Entity* targetEnt, point targetPoint) {
	Job* thisJob = new Job();
	point* Point = new point();
	Point->realX = targetPoint.realX;
	Point->realY = targetPoint.realY;
	Point->tileX = targetPoint.tileX;
	Point->tileY = targetPoint.tileY;
	thisJob->requirements = requirements;
	thisJob->suspended = false;
	thisJob->repeating = false;
	thisJob->assigned = NULL;
	thisJob->targetEnt = targetEnt;
	thisJob->targetPoint = Point;
	thisJob->type = type;
	JobQueue::jobQueue.push_back(thisJob);
}

// Both this function and createJob should probably be moved to a new job factory class
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
							point thisSpot = TileXYToTexXY(x, y);
							createJob(JOB_TYPE_MINING, SKILL_MINING, NULL, thisSpot);
							curMap->setTasked(x,y,true);
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
						if (thisDoodad->hasTags(IS_TREE)) {
							if (doCreateJob) {
								createJob(JOB_TYPE_WOODCUT, SKILL_WOODCUT, thisDoodad, point());
								thisDoodad->tags |= DOODAD_TASKED;
							}
							if (colorize) thisDoodad->spr.setColor(DEFAULT_TILE_COLORS[COLOR_TASKED]);
							if (uncolorize && !thisDoodad->hasTags(DOODAD_TASKED)) thisDoodad->spr.setColor(DEFAULT_TILE_COLORS[COLOR_NONE]);
						}
					}
					break;
				}
				case JOB_TYPE_BUILD:
				{
					// Mining jobs: any tile with the IS_WALKABLE tag is currently able to be turned into a room
					if (curMap->inBounds(x,y) && curMap->isWalkable(x,y)) {
						bool mustUncolorize = false;
						// need to rethink this: where should the color for a tile actually be determined? In map?
						if (colorize) curMap->setColor(x, y, COLOR_TASKED);
					
						if (doCreateJob) {
							point thisSpot = TileXYToTexXY(x, y);
							Item* item = entManager->itemManager->getItemWithTags(IS_WOOD);
							if (item != NULL) {
								item->tasked = true;
								createJob(JOB_TYPE_BUILD, SKILL_MINING, item, thisSpot);
								curMap->setTasked(x,y,true);
							} else {
								mustUncolorize = true;
							}
						}

						if ((uncolorize || mustUncolorize) && !curMap->getTasked(x,y)) curMap->setColor(x, y, COLOR_NONE);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		setOrderMode(ORDER_MODE_BUILD);
	}
};

void ModeOrder::checkUIForClick(float x, float y) {
	if (digButton->isClicked(x,y)) {
		setOrderMode(ORDER_MODE_DIG);
	} else if (woodcutButton->isClicked(x,y)) {
		setOrderMode(ORDER_MODE_CUTTREE);
	} else if (buildButton->isClicked(x,y)) {
		setOrderMode(ORDER_MODE_BUILD);
	}
}

void ModeOrder::handleMouse(sf::RenderWindow* screen) {
	sf::Vector2i mousePos = getMousePos(screen);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!leftClicked && selectionActive == SELECT_TYPE_NONE) { // Initiate clicking
			selectionActive = SELECT_TYPE_LEFT;
			point startPoint = TexXYToTileXY(mousePos.x, mousePos.y);
			selectStartX = startPoint.tileX;
			selectStartY = startPoint.tileY;
			selectLastX = selectStartX;
			selectLastY = selectStartY;
			leftClicked = true;
			checkUIForClick(mousePos.x, mousePos.y);
		} else if (selectionActive == SELECT_TYPE_LEFT) {
			point thisPoint = TexXYToTileXY(mousePos.x, mousePos.y);
			if (thisPoint.tileX != selectLastX || thisPoint.tileY != selectLastY) {
				// redraw
				int jobType;
				if (curOrderType == ORDER_MODE_DIG) {
					jobType = JOB_TYPE_MINING;
				} else if (curOrderType == ORDER_MODE_CUTTREE) {
					jobType = JOB_TYPE_WOODCUT;
				} else if (curOrderType == ORDER_MODE_BUILD) {
					jobType = JOB_TYPE_BUILD;
				}
				findTasksInArea(jobType, selectStartX, selectLastX, selectStartY, selectLastY, false, false, true);
				findTasksInArea(jobType, selectStartX, thisPoint.tileX, selectStartY, thisPoint.tileY, false, true, false);
				selectLastX = thisPoint.tileX;
				selectLastY = thisPoint.tileY;
			}
		}
	} else {
		if (leftClicked && selectionActive == SELECT_TYPE_LEFT) {
			selectionActive = SELECT_TYPE_NONE;
			point endPoint = TexXYToTileXY(mousePos.x, mousePos.y);
			int jobType;
			if (curOrderType == ORDER_MODE_DIG) {
				jobType = JOB_TYPE_MINING;
			} else if (curOrderType == ORDER_MODE_CUTTREE) {
				jobType = JOB_TYPE_WOODCUT;
			} else if (curOrderType == ORDER_MODE_BUILD) {
				jobType = JOB_TYPE_BUILD;
			}
			findTasksInArea(jobType, selectStartX, endPoint.tileX, selectStartY, endPoint.tileY, true, true, false);
		}
		leftClicked = false;
	}

	if (!rightClicked && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		selectionActive = SELECT_TYPE_RIGHT;
		rightClicked = true;
		point clicked = TexXYToTileXY(mousePos.x, mousePos.y);
		point unitPoint = TexXYToTileXY(test->realX, test->realY);
		std::vector<point> route = AStarSearch(curMap, unitPoint.tileX, unitPoint.tileY, clicked.tileX, clicked.tileY);

		if (route.size() != 0) {
			// Remove the last point in the route, since it is the current position
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

void ModeOrder::flushRequests() {
	/*while (!RequestQueues::uiRequests.empty()) {
		// parse this request
		uiRequest request = RequestQueues::uiRequests.back();

		// TODO: Handle this request

 		RequestQueues::uiRequests.pop_back();
	}*/
}

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

// To be moved into a UI container class
void ModeOrder::drawUI(sf::RenderTarget* screen) {
	digButton->render(screen);
	woodcutButton->render(screen);
	buildButton->render(screen);
}

void ModeOrder::render(sf::RenderTarget* screen) {
	sf::Vector2u size = screen->getSize();
	sf::View view = screen->getView();
	view.setCenter(screenX+float(size.x)/2, screenY+float(size.y)/2);
	screen->setView(view);
	curMap->render(screen);
	entManager->render(screen);
	drawUI(screen);
}