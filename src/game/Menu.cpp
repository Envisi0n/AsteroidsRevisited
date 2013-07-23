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

int Menu::update(sf::Vector2i mouseLoc) {

	int action = BUT_NOTHING;
	// Call draw on each button
	for (vector<Button*>::iterator it = buttons.begin(); it != buttons.end();
			++it) {
		if( (action = (*it)->update(mouseLoc)) != BUT_NOTHING )
			return action ;

	}

	return BUT_NOTHING;
}

void Menu::addButton(float x, float y, const char* path, int action) {

	buttons.push_back(new Button(x, y, path, action));

}
