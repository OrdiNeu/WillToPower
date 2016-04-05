#include "ui_drawable.hpp"

UIDrawable::UIDrawable(std::string filename, float screenX, float screenY) : filename(filename), screenX(screenX), screenY(screenY) {
	loadSprite(filename);
}

void UIDrawable::render(sf::RenderTarget* screen) {
	sf::Vector2f screen_center = screen->getView().getCenter();
	spr.setPosition(screenX + screen_center.x, screenY + screen_center.y);
	screen->draw(spr);
}

void UIDrawable::update(float dt) {
}

void UIDrawable::onClick() {
}

bool UIDrawable::isClicked(float x, float y) {
	return x >= screenX &&
		x <= screenX + width &&
		y >= screenY &&
		y <= screenY + height;
}

void UIDrawable::loadSprite(std::string filename) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		DEBUG_OUTPUT << "ERROR: Could not load " << filename << std::endl;
		return;
	};

	width = (int) tex.getSize().x * X_SCALE;
	height = (int) tex.getSize().y * Y_SCALE;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
}