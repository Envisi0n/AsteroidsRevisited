/*
 * GameConnection.cpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 */

#include "GameConnection.hpp"
#include <iostream>

const int headerSize = 16;

GameConnection::GameConnection(unsigned int protocolId, float timeout) {

	setProtocolId(protocolId);
	setTimeout(timeout);
	setMode(None);
	setRunning(false);
	ClearData();

}

GameConnection::~GameConnection() {

	if (isRunning())
		Stop();

}

bool GameConnection::Start(int port) {

	std::cout << "start connection on port " << port << std::endl;

	if (!socket.bind(port))
		return false;
	setRunning(true);
	OnStart();
	return true;

}

void GameConnection::Stop() {

	std::cout << "stop connection" << std::endl;
	ClearData();
	socket.unbind();
	running = false;
	if (isConnected())
		OnDisconnect();
	OnStop();

}

void GameConnection::Listen() {

	std::cout << "server listening for connection" << std::endl;
	ClearData();
	if (isConnected())
		OnDisconnect();
	setMode(Server);
	setState(Listening);
}

void GameConnection::Connect(sf::IpAddress address) {

	std::cout << "client connecting to " << address.toString() << std::endl;
	ClearData();
	if (isConnected())
		OnDisconnect();
	setMode(Client);
	setState(Connecting);
	setAddress(address);

}

void GameConnection::Update(float deltaTime) {

	timeoutAccumulator += deltaTime;
	if (timeoutAccumulator > timeout) {
		if (isConnecting()) {
			std::cout << "connect timed out" << std::endl;
			ClearData();
			setState(ConnectFail);
			OnDisconnect();
		} else if (isConnected()) {
			std::cout << "connection timed out\n" << std::endl;
			ClearData();
			if (isConnecting()) {
				setState(ConnectFail);
			}
			OnDisconnect();
		}
	}

	reliabilitySystem.Update(deltaTime);

}

bool GameConnection::SendPacket(sf::Packet packet) {

	sf::Packet gamePacket;

	if (address == address.None)
		return false;

	// Write packet header
	gamePacket << getProtocolId();
	gamePacket << reliabilitySystem.GetLocalSequence();
	gamePacket << reliabilitySystem.GetRemoteSequence();
	gamePacket << reliabilitySystem.GenerateAckBits();

	// Copy data into packet
	gamePacket << packet.getData();

	socket.send(gamePacket, getAddress(), getPort());

	reliabilitySystem.PacketSent(gamePacket.getDataSize());
	return true;

}

bool GameConnection::SendPacket(sf::Packet packet, sf::IpAddress ipAddress,
		int port) {

	sf::Packet gamePacket;

	if (address == address.None)
		return false;

	// Write packet header
	gamePacket << getProtocolId();
	gamePacket << reliabilitySystem.GetLocalSequence();
	gamePacket << reliabilitySystem.GetRemoteSequence();
	gamePacket << reliabilitySystem.GenerateAckBits();

	// Copy data into packet
	gamePacket << packet.getData();

	socket.send(gamePacket, ipAddress, port);

	reliabilitySystem.PacketSent(gamePacket.getDataSize());
	return true;

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

bool GameConnection::isConnected() const {
	return getState() == Connected;
}

bool GameConnection::isConnecting() const {
	return getState() == Connecting;
}

bool GameConnection::isConnectFailed() const {
	return getState() == ConnectFail;
}

bool GameConnection::isListening() const {
	return getState() == Listening;
}

void GameConnection::ClearData() {

	setState(Disconnected);
	setTimeoutAccumulator(0.0f);
	setAddress(address.None);
	setPort(0);
}
