/*
 * ClientEntity.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "CEntity.hpp"

CEntity::CEntity() {

	if (!texture.loadFromFile("images/test.png")) {
		return;
	}

	sprite.setTexture(texture);
	// TODO Auto-generated constructor stub

}

CEntity::~CEntity() {
	// TODO Auto-generated destructor stub
}

void CEntity::setPosition(float x, float y) {

	setX(x);
	setY(y);

	sprite.setPosition(x,y);

}

void CEntity::draw(sf::RenderWindow* window) {

	window->draw(sprite);
}
