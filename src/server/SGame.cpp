/*
 * SGame.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "SGame.hpp"
#include "../shared/Net_shared.hpp"
#include <iostream>
#include "../shared/GameGlobals.hpp"

SGame::SGame() :
		shellThread(&SGame::shell, this), gameServer(SERVER_PORT) {

	setState(INIT);
	setShellState(SHELL_RUNNING);

}

void SGame::init() {

	std::cout << "Server starting..." << std::endl;

	// Login startup
	std::cout << "Loading users...";
	loginHandler.loadDB();
	std::cout << "done." << std::endl;

	heartBeatTimer.restart();

	setState(RUNNING);

}

void SGame::shutdown() {

	std::cout << "Server shutting down..." << std::endl;
	setState(SHUTDOWN);

	// Login shutdown
	std::cout << "Saving users...";
	loginHandler.saveDB();
	std::cout << "done." << std::endl;

}

void SGame::run() {

	sf::Packet packet;
	int client;

	shellThread.launch();

	while (getState() == RUNNING) {

		// Poll for a packet
		client = gameServer.receive(&packet);

		if (client != -1) {
			handlePacket(client, packet);
		}

		// Update game

		gameWorld.update();

		// Send updates to clients

		gameServer.broadcast(gameWorld.toPacket());

		// Send heartbeat
		if( heartBeatTimer.getElapsedTime().asSeconds() > 5) {
			sendHeartbeats();
			heartBeatTimer.restart();
		}

		sf::sleep(sf::milliseconds(1000 / SERVER_TICK_SPEED));

	}

	shutdown();

}

SGame::~SGame() {
	// TODO Auto-generated destructor stub
}

int SGame::getState() const {

	return state;

}

void SGame::setState(int state) {
	shellMutex.lock();

	this->state = state;

	shellMutex.unlock();
}

void SGame::shell() {

	std::string line;

	while (getShellState() == SHELL_RUNNING) {

		// Print indicator
		std::cout << "[>] ";

		// Get the entered text
		std::getline(std::cin, line);

		// Parse
		if (handleShellCommand(line)) {

			std::cout << "Invalid command" << std::endl;

		}

	}

}

int SGame::handleShellCommand(std::string command) {

	if (command == "stop") {

		setShellState(SHELL_SHUTDOWN);
		setState(SHUTDOWN);
		return 0;
	}

	return 1;
}

int SGame::getShellState() const {
	return shellState;
}

void SGame::setShellState(int shellState) {

	shellMutex.lock();
	this->shellState = shellState;
	shellMutex.unlock();
}

void SGame::handlePacket(int client, sf::Packet packet) {

	short packetType;
	packet >> packetType;

	switch (packetType) {

	case GAMELOGIN:

		loginUser(client, packet);

		break;
	case GAMEREGISTER:

		registerUser(client, packet);

		break;
	case HEARTBEAT:
		std::cout << "Got heartbeat from " << client << std::endl;
		break;

	}

}

void SGame::loginUser(int client, sf::Packet loginInfo) {

	char username[32];
	char password[32];
	struct genericPacket response;
	sf::Packet responsePacket;

	loginInfo >> username;
	loginInfo >> password;

	std::cout << "[ CLIENT [" << client << "] ] ";

	switch (loginHandler.authenticateUser(username, password)) {

	case AUTH_VALID:

		std::cout << username << " authenticated." << std::endl;

		response.packetType = LOGIN_AUTH_VALID;

		break;
	case AUTH_UNKNOWN_USER:

		std::cout << username << " invalid user." << std::endl;

		response.packetType = LOGIN_AUTH_UNKNOWN_USER;

		break;

	case AUTH_INVALID_PASSWORD:

		std::cout << username << " invalid password." << std::endl;

		response.packetType = LOGIN_AUTH_INVALID_PASSWORD;

		break;
	}

	responsePacket << response.packetType;
	gameServer.send(responsePacket, client);

}

void SGame::registerUser(int client, sf::Packet loginInfo) {

	char username[32];
	char password[32];
	struct genericPacket response;
	sf::Packet responsePacket;

	loginInfo >> username;
	loginInfo >> password;

	std::cout << "[ CLIENT [" << client << "] ] ";

	switch (loginHandler.registerUser(username, password)) {
	case REG_SUCCESS:
		std::cout << username << " " << "registered." << std::endl;
		response.packetType = LOGIN_REG_SUCCESS;
		break;
	case REG_INUSE:
		response.packetType = LOGIN_REG_INUSE;
		break;
	}

	responsePacket << response.packetType;
	gameServer.send(responsePacket, client);

}

void SGame::sendHeartbeats() {

	sf::Packet packet;
	genericPacket heartbeat;

	heartbeat.packetType = HEARTBEAT;
	packet << heartbeat;
	gameServer.broadcast(packet);

}
