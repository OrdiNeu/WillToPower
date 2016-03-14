#ifndef MODE_ORDER
#define MODE_ORDER
#include "mode.hpp"
#include "bounds_check.hpp"
#include "constants.hpp"
#include "unit_manager.hpp"
#include <SFML/Graphics.hpp>
#include "job_queue.hpp"
#include "request_queue.hpp"

enum ORDER_MODE {
	ORDER_MODE_DIG,
	ORDER_MODE_CUTTREE
};

enum SELECT_TYPE {
	SELECT_TYPE_NONE,
	SELECT_TYPE_LEFT,
	SELECT_TYPE_RIGHT
};

class ModeOrder : public Mode {
private:
	bool rightClicked, leftClicked;
	int selectionActive;
	int selectStartX, selectStartY;
	int selectLastX, selectLastY;
	Unit* test;
	AI* testai;

	sf::Vector2i getMousePos();
	void findTasksInArea(int type, int x0, int x1, int y0, int y1, bool doCreateJob, bool colorize, bool uncolorize);
	void createJob(int type, int requirements, Entity* targetEnt, point* targetPoint);
	sf::Vector2i getMousePos(sf::RenderWindow* screen);
	void handleKeyboard(float dt);
	void handleMouse(sf::RenderWindow* screen);
	void drawUI();
public:
	float screenX;
	float screenY;
	int curOrderType;
	ModeOrder();
	void init();
	void update(float dt, sf::RenderWindow* screen);
	void render(sf::RenderTarget* screen);
	void setOrderMode(int orderMode);
};

#endif