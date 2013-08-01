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

	virtual ~SGame();
	int getState() const;
	void setState(int state);

private:

	// State of the server
	int state;

	// Login handler
	Login loginHandler;

	// Networking for server
	Server gameServer;

};

#endif /* SGAME_HPP_ */
