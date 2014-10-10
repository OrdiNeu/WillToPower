#include <iostream>
#include "game.hpp"
using namespace std;

int main(int argc, char *argv[]){
	Game game;
	game.init();
	return game.run();
}