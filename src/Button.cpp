/*
 * Button.cpp
 *
 *  Created on: May 11, 2013
 *      Author: David Jelley
 */

#include "Button.hpp"

Button::Button(float x, float y, char* path) {
	sprite.setPosition(x, y);

	if (!texture.loadFromFile(path)) {
		return;
	}

	sprite.setTexture(texture);

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

void Button::draw(sf::RenderWindow* window) {
	window->draw(sprite);

	return ;
}
