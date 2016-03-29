#include "ui_button.hpp"

UIButton::UIButton(std::string filename, float screenX, float screenY) : filename(filename), screenX(screenX), screenY(screenY) {
	loadSprite(filename);
}

void UIButton::render(sf::RenderTarget* screen) {
	spr.setPosition(screenX, screenY);
	screen->draw(spr);
}

void UIButton::update(float dt) {
}

void UIButton::onClick() {
}

bool UIButton::isClicked(float x, float y) {
	return x >= screenX &&
		x <= screenX + width &&
		y >= screenY &&
		y <= screenY + height;
}

void UIButton::loadSprite(std::string filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		DEBUG_OUTPUT << "ERROR: Could not load " << filename << std::endl;
		return;
	};

	width = (int) tex.getSize().x;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
}