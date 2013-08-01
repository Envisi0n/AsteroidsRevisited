/*
 * SGame.hpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#ifndef SGAME_HPP_
#define SGAME_HPP_

#include "Server.hpp"
#include "Login.hpp"

enum gameState {

	INIT, RUNNING, SHUTDOWN

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

private:

	void handlePacket(int client, sf::Packet packet);

	// State of the server
	int state;

	// Login handler
	Login loginHandler;
	void loginUser( int client, sf::Packet loginInfo );
	void registerUser( int client, sf::Packet loginInfo );


	// Networking for server
	Server gameServer;

};

#endif /* SGAME_HPP_ */
