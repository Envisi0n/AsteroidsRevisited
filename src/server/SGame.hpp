/*
 * SGame.hpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#ifndef SGAME_HPP_
#define SGAME_HPP_

#include <SFML/System.hpp>
#include "Server.hpp"
#include "Login.hpp"
#include "../shared/World.hpp"
#include <string>

enum gameState {

	INIT, RUNNING, SHUTDOWN

};

enum shellState {

	SHELL_RUNNING, SHELL_SHUTDOWN

};

class SGame {
public:
	SGame();
	virtual void init();
	virtual void run();
	virtual void shutdown();

	virtual ~SGame();
	int getState() const;
	void setState(int state);
	int getShellState() const;
	void setShellState(int shellState);

private:

	// Asteroids game
	World gameWorld;
	void updateClient( int client, sf::Packet clientUpdate);

	// Shell
	int shellState;
	sf::Thread shellThread;
	void shell();
	int handleShellCommand(std::string command);
	sf::Mutex shellMutex;

	// State of the server
	int state;
	// Login handler
	Login loginHandler;
	void loginUser( int client, sf::Packet loginInfo );
	void registerUser( int client, sf::Packet loginInfo );

	// Networking for server
	Server gameServer;
	void handlePacket(int client, sf::Packet packet);
	sf::Clock heartBeatTimer;
	void sendHeartbeats();
	sf::Clock test;

};

#endif /* SGAME_HPP_ */
