#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.hpp"
#include "mode.hpp"

class Game {
	private:
		sf::RenderWindow screen;
		Mode* curMode;
	public:
		bool init();
		int run();
		void update(float dt);
		void render();
};

#endif