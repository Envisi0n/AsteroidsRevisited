/*
 * CGame.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "CGame.hpp"

CGame::CGame() {
	setState(INIT);
}

CGame::~CGame() {
	// TODO Auto-generated destructor stub
}

void CGame::init() {

	// Init the background.
	background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	if (!backgroundImage.loadFromFile("images/background.png"))
		return; // Error message here.

	background.setTexture(&backgroundImage);

	// Init the Main Menu

	gameMenu.addButton(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, "images/test.png");

	setState(MENU);

}

void CGame::run() {

	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids",
			sf::Style::Titlebar | sf::Style::Close);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		switch(getState()) {
		case INIT:
			// Error message here.
			break;
		case MENU:
			// Draw the background.
			window.clear();
			window.draw(background);
			// Draw menu buttons.
			gameMenu.draw(&window);
			window.display();
			break;
		case PLAYING:
			break;
		case PAUSE:
			break;
		case QUIT:
			break;
		default:
			// Error message here.
			break;
		}

	}

}

void CGame::update() {
}

int CGame::getState() const {
	return state;
}

void CGame::setState(int state) {
	this->state = state;
}
