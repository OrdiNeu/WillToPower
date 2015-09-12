#ifndef DOODAD_HPP
#define DOODAD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "job_queue.hpp"

// For those who don't know Blizzard terminology: doodads are background fixtures that do not have AI, and generally do less than units
// They may still have HP, but they definitely have no kinesthetics
class Doodad : public Entity {
private:
	int halfWidth, height;
public:
	sf::Sprite spr;
	sf::Texture tex;
	std::string filename;
	Doodad();
	Doodad(std::string ID, std::string filename, int x, int y);
	Doodad* clone();
	void render(sf::RenderTarget* screen);
	void update(float dt);
};

#endif