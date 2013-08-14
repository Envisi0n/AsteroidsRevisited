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

#define SERVER_TICK_SPEED 33
#define TICKS_PER_SECOND 33
#define SKIP_TICKS 1000 / TICKS_PER_SECOND
#define MAX_FRAMESKIP 5

// Client input
enum userInput {

	THRUSTUP,
	THRUSTDOWN,
	TURNLEFT,
	TURNRIGHT,

};


#endif /* GAMEGLOBALS_HPP_ */
