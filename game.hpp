#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mode.hpp"
#include "mode_main_menu.hpp"
#include "mode_map_edit.hpp"
#include "mode_order.hpp"
#include "entity_manager.hpp"
#include "world_generator.hpp"
#include "PerlinNoiseGenerator.hpp"
#include "xml_loader.hpp"

class Game {
	private:
		sf::RenderWindow screen;
		Mode* curMode;
	public:
		bool init();
		int run();
		void update(float dt);
		void render();
		~Game();
};

#endif