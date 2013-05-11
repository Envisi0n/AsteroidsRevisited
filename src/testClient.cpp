/*
 * testClient.cpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */
#include "Client.hpp"

#include <iostream>

int main( int argc, char *argv[] ) {

	Client test;
	char buf[32];
	sf::Packet testPacket;

	testPacket << "Ping";

	test.setServerAddress("127.0.0.1");
	test.setServerPort(30000);

	test.send(testPacket);

	if( test.receive(&testPacket) == sf::Socket::Done ) {

		testPacket >> buf;

		std::cout << "Recieved: " << buf << std::endl;


	}




	return 0;

}



