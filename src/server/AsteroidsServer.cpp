/*
 * AsteroidsServer.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: cameron
 */

#include "SGame.hpp"

int main( int argc, char *argv[] ) {

	SGame server;

	server.init();

	server.run();
       
	return 0;
}
