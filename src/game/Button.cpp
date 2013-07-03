/*
 * Button.cpp
 *
 *  Created on: May 11, 2013
 *      Author: David Jelley
 */

#include "Button.hpp"

Button::Button(float x, float y, const char* texturePath, void (*fun)()) {
	setPosition(x, y);

	if (!texture.loadFromFile(texturePath)) {
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

void Button::runAction() {

	action();
}

void Button::setPosition(float x, float y) {

	this->sprite.setPosition(x, y);
}
