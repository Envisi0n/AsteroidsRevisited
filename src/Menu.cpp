/*
 * Menu.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "Menu.hpp"

Menu::Menu() {
	// TODO Auto-generated constructor stub

}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

void Menu::draw(sf::RenderWindow* window) {

	for (vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

		(*it)->draw(window);

	}

}

void Menu::addButton(int height, int width, int x, int y, char* path) {
}
