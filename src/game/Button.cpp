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

void Button::animate(int color) {

	switch( color ) {

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
void Button::update(sf::Vector2i mouseLoc) {

	sf::Vector2f tmp;
	tmp.x = mouseLoc.x;
	tmp.y = mouseLoc.y;

	if( sprite.getGlobalBounds().contains(tmp)) {

		if( sf::Mouse::isButtonPressed(sf::Mouse::Left))
			animate(CLICK);
		else
			animate(OVER);

	}
	else
		animate(NORMAL);


}
