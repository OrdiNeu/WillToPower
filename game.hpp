#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.hpp"
#include "mode.hpp"
#include "mode_main_menu.hpp"
#include "mode_map_edit.hpp"
#include "mode_order.hpp"
#include "unit_manager.hpp"
#include "entity_manager.hpp"

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