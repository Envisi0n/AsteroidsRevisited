/*
 * Player.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: Cam
 */

#include "Player.hpp"

Player::Player(int clientID) {
	setClientId(clientID);

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

int Player::getClientId() const {
	return clientID;
}

void Player::setClientId(int clientId) {
	clientID = clientId;
}
