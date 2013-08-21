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

	socket.setBlocking(false);
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
		unsigned short port, GameReliabilitySystem & clientInstance) {

	sf::Packet gamePacket;

	if (address == address.None)
		return false;

	// Write packet header
	gamePacket << getProtocolId();
	gamePacket << clientInstance.GetLocalSequence();
	gamePacket << clientInstance.GetRemoteSequence();
	gamePacket << clientInstance.GenerateAckBits();

	// Copy data into packet
	gamePacket << packet.getData();

	socket.send(gamePacket, ipAddress, port);

	clientInstance.PacketSent(gamePacket.getDataSize());
	return true;

}

int GameConnection::ReceivePacket(sf::Packet *packet) {

	int received_bytes;
	unsigned int protocol, seq, ack, ack_bits;

	socket.receive(*packet, address, port);

	if ((received_bytes = packet->getDataSize()) < 12)
		return 0;

	*packet >> protocol;
	*packet >> seq;
	*packet >> ack;
	*packet >> ack_bits;

	reliabilitySystem.PacketReceived(seq, received_bytes - headerSize);
	reliabilitySystem.ProcessAck(ack, ack_bits);

	return packet->getDataSize();

}

int GameConnection::ReceivePacket(sf::Packet *packet, sf::IpAddress *ipAddress,
		unsigned short *port, GameReliabilitySystem & clientInstance) {

	int received_bytes;
	unsigned int protocol, seq, ack, ack_bits;

	socket.receive(*packet, *ipAddress, *port);

	if ((received_bytes = packet->getDataSize()) < 12)
		return 0;

	*packet >> protocol;
	*packet >> seq;
	*packet >> ack;
	*packet >> ack_bits;

	clientInstance.PacketReceived(seq, received_bytes - headerSize);
	clientInstance.ProcessAck(ack, ack_bits);

	return packet->getDataSize();

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

unsigned short GameConnection::getPort() const {
	return port;
}

void GameConnection::setPort(unsigned short port) {
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
	reliabilitySystem.Reset();
}
