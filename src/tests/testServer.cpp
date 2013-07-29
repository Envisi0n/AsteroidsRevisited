/*
 * testServer.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "../server/Server.hpp"
#include "../server/Login.hpp"
#include "../game/Net_shared.hpp"
#include <iostream>
int main(int argc, char *argv[]) {

	Login loginHandler;
	Server test(30000);
	sf::Packet testPacket;
	while (1) {
		if (test.receive(&testPacket) == sf::Socket::Done) {

			short packetType;
			struct loginPacket login;

			testPacket >> packetType;

			switch (packetType) {

			case GAMELOGIN:
				testPacket >> login.username;
				testPacket >> login.password;

				if (loginHandler.authenticateUser(login.username,
						login.password) == AUTH_VALID) {

					std::cout << login.username << " authenticated."
							<< std::endl;
					return 0;
				}

				break;

			case GAMEREGISTER:
				testPacket >> login.username;
				testPacket >> login.password;

				if (loginHandler.registerUser(login.username, login.password)
						== REG_SUCCESS) {
					std::cout << login.username << " registered." << std::endl;
					return 0;
				}
				break;

			}
			std::cout << "Received: " << packetType << std::endl;

			testPacket.clear();
		}
	}

	return 0;
}
