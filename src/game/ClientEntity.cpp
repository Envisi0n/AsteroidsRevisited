/*
 * ClientEntity.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: Cam
 */

#include "ClientEntity.hpp"

ClientEntity::ClientEntity() {

	if (!texture.loadFromFile("images/test.png")) {
		return;
	}

	sprite.setTexture(texture);
	// TODO Auto-generated constructor stub

}

ClientEntity::~ClientEntity() {
	// TODO Auto-generated destructor stub
}

void ClientEntity::draw(sf::RenderWindow* window) {

	window->draw(sprite);
}
