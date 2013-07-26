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

				char buf[32];

				testPacket >> buf;

				std::cout << "Received: " << buf << std::endl;

				testPacket.clear();
				testPacket << buf;

				test.send(testPacket, 0);

			}
	}

	return 0;
}
