/*
 * Button.cpp
 *
 *  Created on: May 11, 2013
 *      Author: David Jelley
 */

#include "Button.hpp"

Button::Button(float x, float y, const char* texturePath, int action) {
	setPosition(x, y);
	setAction(action);
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

	return;
}

void Button::setPosition(float x, float y) {

	this->sprite.setPosition(x, y);
}

void Button::animate(int color) {

	// Don't animate if this button does nothing
	if (getAction() == BUT_NOTHING)
		return;

	switch (color) {

	case NORMAL:
		this->sprite.setColor(sf::Color(255, 255, 255));
		break;
	case OVER:
		this->sprite.setColor(sf::Color(255, 255, 0));
		break;
	case CLICK:
		this->sprite.setColor(sf::Color(0, 255, 0));
		break;

	}

}
int Button::update(sf::Vector2i mouseLoc, sf::Event event) {

	sf::Vector2f tmp;
	tmp.x = mouseLoc.x;
	tmp.y = mouseLoc.y;

	if (sprite.getGlobalBounds().contains(tmp)) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			animate(CLICK);
			return action;
		} else {
			animate(OVER);
			return BUT_NOTHING;
		}

	} else
		animate(NORMAL);

	return BUT_NOTHING;

}

int Button::getAction() const {
	return action;
}

void Button::setAction(int action) {
	this->action = action;
}
