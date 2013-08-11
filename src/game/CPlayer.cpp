/*
 * CPlayer.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Cam
 */

#include "CPlayer.hpp"

CPlayer::CPlayer() {
	// TODO Auto-generated constructor stub

}

CPlayer::~CPlayer() {
	// TODO Auto-generated destructor stub
}

void CPlayer::draw(sf::RenderWindow* window) {
	ship.draw(window);
}

void CPlayer::setShipTexture(sf::Texture* texture) {
	ship.setTexture(texture);
}
