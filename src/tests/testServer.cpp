/*
 * testServer.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "../game/Server.hpp"
#include <iostream>
int main(int argc, char *argv[]) {

	Server test(30000);
	sf::Packet testPacket;
	while (1) {
		if (test.receive(&testPacket) == sf::Socket::Done) {

			short packetType;

			testPacket >> packetType;

			std::cout << "Received: " << packetType << std::endl;

			testPacket.clear();
		}
	}

	return 0;
}
