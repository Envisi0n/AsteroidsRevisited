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
#include <sstream>

SGame::SGame() :
		shellThread(&SGame::shell, this) {

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

	// Disconnect clients
	gameServer.disconnectAll();

	// Login shutdown
	std::cout << "Saving users...";
	loginHandler.saveDB();
	std::cout << "done." << std::endl;

}

void SGame::run() {

	sf::Packet packet;
	int client;

	shellThread.launch();

	int loops;
	sf::Clock gameClock;
	float nextTick = gameClock.getElapsedTime().asMilliseconds();
	sf::Clock delta;
	float sendAc = 0;
	float sendRate = 30;

	while (getState() == RUNNING) {

		loops = 0;
		while (gameClock.getElapsedTime().asMilliseconds() > nextTick
				&& loops < MAX_FRAMESKIP) {

			// Poll for a packet
			while ((client = gameServer.receive(&packet)) != -1) {

				handlePacket(client, packet);
			}
			packet.clear();
			// Update game

			gameWorld.update();
			// Send updates to clients

			gameServer.broadcast(gameWorld.toPacket());


			gameServer.update(1.0f/TICKS_PER_SECOND);
			//Send heartbeat
			if (heartBeatTimer.getElapsedTime().asSeconds() > 5) {

				gameServer.printStats();
				heartBeatTimer.restart();
			}

			nextTick += SKIP_TICKS;
			loops++;
		}

		// This tells the OS to give up the remaining timeslice
		sf::sleep(sf::milliseconds(0));

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

	std::stringstream commandStream(command);
	std::string arg;

	commandStream >> arg;

	if (arg == "stop") {

		setShellState(SHELL_SHUTDOWN);
		setState(SHUTDOWN);
		return 0;
	}

	if (arg == "kick") {

		int client;

		commandStream >> client;

		gameServer.disconnectClient(client);
		return 0;

	}

	if (arg == "add") {

		std::cout << "added entity" << std::endl;
		gameWorld.addEntity();
		return 0;
	}

	if( arg == "list" ) {

		gameServer.printClients();
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
		//	std::cout << "Got heartbeat from " << client << " "
		//			<< test.getElapsedTime().asMilliseconds() << std::endl;
		break;
	case CLIENT_UPDATE:
		updateClient(client, packet);
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

		gameWorld.createPlayer(client, username);
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
	if (!gameServer.send(responsePacket, client)) {
		std::cout << "failed to send login response to: " << client
				<< std::endl;
	}

	// Disconnect bad sessions
	if (response.packetType == LOGIN_AUTH_UNKNOWN_USER
			|| response.packetType == LOGIN_AUTH_INVALID_PASSWORD) {
		std::cout << "Disconnecting...login" << std::endl;
		gameServer.disconnectClient(client);
	}

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
		gameWorld.createPlayer(client, username);
		break;
	case REG_INUSE:
		response.packetType = LOGIN_REG_INUSE;
		break;
	}

	responsePacket << response.packetType;
	gameServer.send(responsePacket, client);

	// Disconnect bad sessions
	if (response.packetType == LOGIN_REG_INUSE) {
		gameServer.disconnectClient(client);
	}

}

void SGame::updateClient(int client, sf::Packet clientUpdate) {

	gameWorld.updatePlayer(client, clientUpdate);

}

void SGame::sendHeartbeats() {

	sf::Packet packet;
	genericPacket heartbeat;

	heartbeat.packetType = HEARTBEAT;
	packet << heartbeat;
	gameServer.broadcast(packet);
	test.restart();

}
