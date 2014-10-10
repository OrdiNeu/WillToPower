#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.hpp"

class Game {
	private:
		sf::RenderWindow screen;
		Map curMap;
	public:
		bool init();
		int run();
		void update(float dt);
		void render();
};

#endif