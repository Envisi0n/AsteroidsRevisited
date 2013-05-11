/*
 * Main.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main(int argc, char *argv[]) {

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
			"Asteroids",sf::Style::Titlebar|sf::Style::Close);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

}

