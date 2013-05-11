/*
 * Main.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include <SFML/Graphics.hpp>
#include "CGame.hpp"

int main(int argc, char *argv[]) {

	CGame game;

	game.init();

	game.run();

	return 0;

}

