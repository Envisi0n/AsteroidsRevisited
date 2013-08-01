/*
 * SGame.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "SGame.hpp"
#include "../shared/Net_shared.hpp"

SGame::SGame() : gameServer(SERVER_PORT) {

	setState(INIT);


}

void SGame::init() {
}

void SGame::run() {
}

SGame::~SGame() {
	// TODO Auto-generated destructor stub
}

int SGame::getState() const {
	return state;
}

void SGame::setState(int state) {
	this->state = state;
}
