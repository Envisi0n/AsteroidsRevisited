/*
 * GameGlobals.hpp
 *
 *  Created on: Aug 2, 2013
 *      Author: Cam
 */

#ifndef GAMEGLOBALS_HPP_
#define GAMEGLOBALS_HPP_

#define WORLD_WIDTH 800
#define WORLD_HEIGHT 600

#define TICKS_PER_SECOND 30
#define SKIP_TICKS 1000 / TICKS_PER_SECOND
#define MAX_FRAMESKIP 5

// Networking
#define SERVER_PORT 30000
#define CLIENT_PORT 30001
#define PROTOCOL 1
#define TIMEOUT 10


// Client input
enum userInput {

	THRUSTUP,
	THRUSTDOWN,
	TURNLEFT,
	TURNRIGHT,

};


#endif /* GAMEGLOBALS_HPP_ */
