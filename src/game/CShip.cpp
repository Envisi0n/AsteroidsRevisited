/*
 * CShip.cpp
 *
 *  Created on: Aug 9, 2013
 *      Author: Cam
 */

#include "CShip.hpp"
#include <iostream>
#include <cmath>

CShip::CShip(float x, float y, float velX, float velY, float rotation,
		sf::Texture *texture) :
		Ship(x, y, velX, velY, rotation) {

	float w, h;

	sprite.setTexture(*texture);

	init();

}

CShip::~CShip() {
	// TODO Auto-generated destructor stub
}

CShip::CShip() {
}

void CShip::init() {

	float w = sprite.getTexture()->getSize().x;
	float h = sprite.getTexture()->getSize().y;

	sprite.setOrigin(w / 2, h / 2);
}

void CShip::draw(sf::RenderWindow* window, float interpolation) {

	float iX = getX() + (getVelX() * interpolation);
	float iY = getY() + (getVelY() * interpolation);

	// Calculate point ahead of ship to point to
	float rads = getRotation()/3.14*180;
	float px = iX-30*std::cos(rads);
	float py = iY-30*std::sin(rads);
	sprite.setPosition(iX, iY);
	// Set rotation at the point
	sprite.setRotation( -std::atan2(px - iX, py - iY)*180/3.14);
	window->draw(sprite);
}

void CShip::setTexture(sf::Texture* texture) {
	sprite.setTexture(*texture);
}

void CShip::update(float x, float y, float rotation) {

	setX(x);
	setY(y);
	setRotation(rotation);

}
