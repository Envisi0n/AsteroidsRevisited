/*
 * testServer.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "../game/Server.hpp"
#include "../game/Net_shared.hpp"
#include <iostream>
int main(int argc, char *argv[]) {

	Server test(30000);
	sf::Packet testPacket;
	while (1) {
		if (test.receive(&testPacket) == sf::Socket::Done) {

			short packetType;

			testPacket >> packetType;

			switch( packetType) {

			case GAMELOGIN:

				struct loginPacket login;

				testPacket >> login.username;
				testPacket >> login.password;

				std::cout << "Username: " << login.username << " " <<  "Password: " << login.password << std::endl;


				break;

			}
			std::cout << "Received: " << packetType << std::endl;

			testPacket.clear();
		}
	}

	return 0;
}
