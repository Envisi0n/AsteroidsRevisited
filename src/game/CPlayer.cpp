/*
 * CPlayer.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Cam
 */

#include "CPlayer.hpp"
#include <iostream>
CPlayer::CPlayer() {
	// TODO Auto-generated constructor stub

}

CPlayer::~CPlayer() {
	// TODO Auto-generated destructor stub
}

void CPlayer::draw(sf::RenderWindow* window, float interpolation) {
	clientShip.draw(window,interpolation);
}

void CPlayer::setShipTexture(sf::Texture* texture) {
	clientShip.setTexture(texture);
	clientShip.init();
}

void CPlayer::updateShip(float x, float y, float rotation) {
	clientShip.update(x,y,rotation);
}

unsigned int CPlayer::getShipID() {
	return clientShip.getId();
}

float CPlayer::getShipX() {
	return clientShip.getX();
}

float CPlayer::getShipY() {
	return clientShip.getY();
}

void CPlayer::fromPacket(sf::Packet* packet) {

	int clientID;
	float ping;
	std::string userName;

	*packet >> clientID;
	*packet >> userName;
	*packet >> ping;

	setClientId(clientID);
	setUserName(userName);
	setPing(ping);

	clientShip.fromPacket(packet);


}

float CPlayer::getShipRotation() {
	return clientShip.getRotation();
}
