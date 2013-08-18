/*
 * CShip.cpp
 *
 *  Created on: Aug 9, 2013
 *      Author: Cam
 */

#include "CShip.hpp"

CShip::CShip(float x, float y, float velX, float velY, float rotation,
		sf::Texture *texture) :
		Ship(x, y, velX, velY, rotation) {

	sprite.setTexture(*texture);

}

CShip::~CShip() {
	// TODO Auto-generated destructor stub
}

CShip::CShip() {
}

void CShip::draw(sf::RenderWindow* window, float interpolation) {
	float iX = getX() + (getVelX() * interpolation);
	float iY = getY() + (getVelY() * interpolation);

	sprite.setPosition(iX, iY);
	window->draw(sprite);
}

void CShip::setTexture(sf::Texture* texture) {
	sprite.setTexture(*texture);
}

void CShip::setPosition(float x, float y) {

	setX(x);
	setY(y);

	sprite.setPosition(getX(), getY());

}
