#include "ui_container.hpp"

void UIContainer::render(sf::RenderTarget* screen) {
	for (UIDrawable* thisUI : components) {
		thisUI->render(screen);
	}
}

void UIContainer::update(float dt) {
	for (UIDrawable* thisUI : components) {
		thisUI->update(dt);
	}
};