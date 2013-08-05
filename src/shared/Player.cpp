/*
 * Player.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: Cam
 */

#include "Player.hpp"

Player::Player(int clientID, std::string userName) {
	setClientId(clientID);
	setUserName(userName);

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

const std::string& Player::getUserName() const {
	return userName;
}

void Player::setUserName(const std::string& userName) {
	this->userName = userName;
}
