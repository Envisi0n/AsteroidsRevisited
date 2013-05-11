/*
 * testServer.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "Server.hpp"
#include <iostream>
int main( int argc, char *argv[] ) {

	Server test(30000);
	sf::Packet testPacket;
	while( 1 )
	if( test.receive(&testPacket,0) == sf::Socket::Done) {

		char buf[32];

		testPacket >> buf;

		std::cout << "Received: " << buf << std::endl;


		testPacket.clear();
		testPacket << "Pong";

		test.send(testPacket,0);


	}



	return 0;
}
