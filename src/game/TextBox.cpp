/*
 * TextBox.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Dave
 */

#include "TextBox.hpp"

TextBox::TextBox(float x, float y, int paramWidth) {
	setPosition(x, y);
}

TextBox::~TextBox() {
	// TODO Auto-generated destructor stub
}

void TextBox::draw(sf::RenderWindow* window) {
	window->draw(rectangle);

	return ;
}

void TextBox::setPosition(float x, float y) {

	this->rectangle.setPosition(x, y);
}

