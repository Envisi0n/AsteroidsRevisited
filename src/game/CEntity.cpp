/*
 * ClientEntity.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "CEntity.hpp"
#include <iostream>
CEntity::CEntity() {

	if (!texture.loadFromFile("images/test.png")) {
		return;
	}

	sprite.setTexture(texture);

}

CEntity::CEntity(float x, float y) :
		Entity(x, y) {

	if (!texture.loadFromFile("images/test.png")) {
		return;
	}

	sprite.setTexture(texture);

}

CEntity::~CEntity() {
	// TODO Auto-generated destructor stub
}

void CEntity::setPosition(float x, float y) {

	setX(x);
	setY(y);

	sprite.setPosition(getX(), getY());

}

void CEntity::draw(sf::RenderWindow* window) {

	window->draw(sprite);
}

void CEntity::update(sf::Event event) {



}
