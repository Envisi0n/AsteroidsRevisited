/*
 * GameConnection.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 */

#include "GameConnection.hpp"

GameConnection::GameConnection(unsigned int protocolId, float timeout) {

	setProtocolId(protocolId);
	setTimeout(timeout);
	setMode(None);
	setRunning(false);
	ClearData();

}

GameConnection::~GameConnection() {

}

sf::IpAddress GameConnection::getAddress() const {
	return address;
}

void GameConnection::setAddress(sf::IpAddress address) {
	this->address = address;
}

Mode GameConnection::getMode() const {
	return mode;
}

void GameConnection::setMode(Mode mode) {
	this->mode = mode;
}

int GameConnection::getPort() const {
	return port;
}

void GameConnection::setPort(int port) {
	this->port = port;
}

unsigned int GameConnection::getProtocolId() const {
	return protocolId;
}

void GameConnection::setProtocolId(unsigned int protocolId) {
	this->protocolId = protocolId;
}

bool GameConnection::isRunning() const {
	return running;
}

void GameConnection::setRunning(bool running) {
	this->running = running;
}

State GameConnection::getState() const {
	return state;
}

void GameConnection::setState(State state) {
	this->state = state;
}

float GameConnection::getTimeout() const {
	return timeout;
}

void GameConnection::setTimeout(float timeout) {
	this->timeout = timeout;
}

float GameConnection::getTimeoutAccumulator() const {
	return timeoutAccumulator;
}

void GameConnection::setTimeoutAccumulator(float timeoutAccumulator) {
	this->timeoutAccumulator = timeoutAccumulator;
}

void GameConnection::ClearData() {

	setState(Disconnected);
	setTimeoutAccumulator(0.0f);
	setAddress(address.None);
	setPort(0);
}
