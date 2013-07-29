/*
 * Menu.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "Menu.hpp"
#include <iostream>

sf::Clock Menu::reset;


Menu::Menu() {

	reset.restart();

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

	// Call draw on each textbox
	for (vector<TextBox*>::iterator it = TextBoxes.begin(); it != TextBoxes.end();
			++it) {

		(*it)->draw(window);

	}

}

int Menu::update(sf::Vector2i mouseLoc, sf::Event event) {

	int action = BUT_NOTHING;
	// Call draw on each button
	for (vector<Button*>::iterator it = buttons.begin(); it != buttons.end();
			++it) {
		if ((action = (*it)->update(mouseLoc, event))
				!= BUT_NOTHING && reset.getElapsedTime().asSeconds() > CLICK_DELAY) {
			reset.restart();
			return action;
		}
	}

	for (vector<TextBox*>::iterator it = TextBoxes.begin(); it != TextBoxes.end(); ++it) {
		(*it)->update(mouseLoc, event);
	}

	return BUT_NOTHING;
}

void Menu::addButton(float x, float y, const char* path, int action) {

	buttons.push_back(new Button(x, y, path, action));

}

void Menu::addTextBox(float x, float y, float pWidth) {

	TextBoxes.push_back(new TextBox(x, y, pWidth));

}
