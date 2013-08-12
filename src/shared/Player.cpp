/*
 * Player.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: Cam
 */

#include "Player.hpp"
#include <sstream>
#include <iostream>

Player::Player() {
	setClientId(-1);
	setUserName("<invalid>");
}

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

void Player::update() {

	ship.update();

}

void Player::shipUpdate(int clientAction) {

	ship.clientUpdate(clientAction);
}

void Player::setUserName(const std::string& userName) {
	this->userName = userName;
}

void Player::toPacket(sf::Packet* packet) {

	// Extract player info
	*packet << getClientId();
	*packet << getUserName();
	*packet << getPing();

	// Extract ship info
	ship.toPacket(packet);

}

void Player::fromPacket(sf::Packet* packet) {

	int clientID;
	float ping;
	std::string userName;

	*packet >> clientID;
	*packet >> userName;
	*packet >> ping;

	setClientId(clientID);
	setUserName(userName);
	setPing(ping);

	ship.fromPacket(packet);


}

std::string Player::toString() {

	std::stringstream tmp;

	tmp << getUserName() << "[" << getClientId() << "] : ";
	tmp << "Ping: " << getPing() << " ";
	tmp << "Ship info: " << ship.toString();

	return tmp.str();

}

float Player::getLastSeen() const {
	return lastSeen;
}

void Player::setLastSeen(float lastSeen) {
	this->lastSeen = lastSeen;
}

float Player::getPing() const {
	return ping;
}

void Player::setPing(float ping) {
	this->ping = ping;
}
