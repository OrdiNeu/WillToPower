#ifndef UI_DRAWABLE_HPP
#define UI_DRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "request_queue.hpp"

class UIDrawable {
protected:
	float width;
	float height;
	std::string filename;
public:
	sf::Sprite spr;
	sf::Texture tex;
	float screenX, screenY;
	float dx, dy;

	UIDrawable(std::string filename, float screenX, float screenY);
	void loadSprite(std::string filename);
	virtual void render(sf::RenderTarget* screen);
	virtual void update(float dt);
	virtual void onClick();
	virtual bool isClicked(float x, float y);
};

#endif