#ifndef UI_CONTAINER_HPP
#define UI_CONTAINER_HPP

#include "ui_drawable.hpp"

class UIContainer {
public:
	std::vector<UIDrawable*> components;
	void render(sf::RenderTarget* screen);
	void update(float dt);
};

#endif