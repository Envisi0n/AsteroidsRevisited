/*
 * Menu.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "Menu.hpp"

Menu::Menu() {

}

Menu::~Menu() {
	// Delete all the buttons
	for (vector<Button*>::iterator it = buttons.begin(); it != buttons.end();
			++it) {

		delete *it;

	}
}

void Menu::draw(sf::RenderWindow* window) {
	// Call draw on each button
	for (vector<Button*>::iterator it = buttons.begin(); it != buttons.end();
			++it) {

		(*it)->draw(window);

	}

}

void Menu::addButton(float x, float y, const char* path) {

	buttons.push_back(new Button(x, y, path));

}
