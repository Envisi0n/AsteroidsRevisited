/*
 * SGame.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "SGame.hpp"
#include "../shared/Net_shared.hpp"
#include <iostream>

SGame::SGame() : gameServer(SERVER_PORT) {

	setState(INIT);

}

void SGame::init() {

	std::cout << "Server starting..." << std::endl;

	std::cout << "Loading users...";
	loginHandler.loadDB();
	std::cout << "done." << std::endl;


	setState(RUNNING);

}

void SGame::run() {

	while( getState() == RUNNING ) {

	}

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
