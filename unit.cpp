#include "unit.hpp"
using namespace std;

std::vector<Unit*> Unit::units;

Unit::Unit() {
}

Unit::Unit(std::string filename, int x, int y) : filename(filename), x(x), y(y) {
	if (filename != "EMPTY" && !tex.loadFromFile(filename)) {
		cout << "ERROR: Could not load " << filename << endl;
		return;
	};
	halfWidth = (int) tex.getSize().x / 2;
	height = (int) tex.getSize().y;
	spr.setTexture(tex);
	spr.setScale(X_SCALE, Y_SCALE);
	units.push_back(this);
}

void Unit::render(sf::RenderTarget* screen) {
	spr.setPosition(x - halfWidth, y - height);
	screen->draw(spr);
}

void Unit::update(float dt) {

}