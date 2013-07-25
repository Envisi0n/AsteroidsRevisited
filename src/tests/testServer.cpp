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
		for (int i = 0; i < MAXCLIENTS; i++)
			if (test.receive(&testPacket, i) == sf::Socket::Done) {

				char buf[32];

				testPacket >> buf;

				std::cout << "Received: " << buf << std::endl;

				testPacket.clear();
				testPacket << buf;

				test.send(testPacket, i);

			}
	}

	return 0;
}
