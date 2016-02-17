#ifndef MODE_ORDER
#define MODE_ORDER
#include "mode.hpp"
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
	bool rightClicked;
	bool leftClicked;
	int selectionActive;
	int selectStartX;
	int selectStartY;
	int selectLastX;
	int selectLastY;
	Unit* test;
	AI* testai;
	sf::Sprite selectionTile;
	sf::Sprite selectionSprite;
	sf::RenderTexture selectionTex;
	sf::Vector2i getMousePos();
	void rerenderSelection();
	void findTasksInArea(int type, int x0, int x1, int y0, int y1, bool doCreateJob, bool colorize, bool uncolorize);
	void createJob(int type, int requirements, Entity* targetEnt, point* targetPoint);
	sf::Vector2i getMousePos(sf::RenderWindow* screen);
	void rerenderSelection(sf::RenderWindow* screen);
	void checkBounds(int* x0, int* x1);
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