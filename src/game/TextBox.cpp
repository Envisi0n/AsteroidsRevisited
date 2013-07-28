/*
 * TextBox.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Dave
 */

#include "TextBox.hpp"

TextBox::TextBox(float x, float y, float pWidth) {
	setPosition(x, y);
	setSize(pWidth);
	setHasFocus (FALSE);
}

TextBox::~TextBox() {
	// TODO Auto-generated destructor stub
}

void TextBox::draw(sf::RenderWindow* window) {
	window->draw(rectangle);

	return;
}

void TextBox::setPosition(float x, float y) {

	this->rectangle.setPosition(x, y);
}

void TextBox::setSize(float pWidth) {

	this->rectangle.setSize(sf::Vector2f(pWidth, 20));
}

void TextBox::update(sf::Vector2i mouseLoc, sf::Event event) {

	sf::Vector2f tmp;
	tmp.x = mouseLoc.x;
	tmp.y = mouseLoc.y;

	bool Focus = isHasFocus();

	if (rectangle.getGlobalBounds().contains(tmp)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			setHasFocus (TRUE);

		}
	} else {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			setHasFocus (TRUE);

		}
	}

	if (Focus) { //Key is pressed.

	}
}

bool TextBox::isHasFocus() const {
	return hasFocus;
}

void TextBox::setHasFocus(bool hasFocus) {
	this->hasFocus = hasFocus;
}
