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
	int client;
	while (1) {
		if ((client = test.receive(&testPacket)) != -1) {

			short packetType;
			struct loginPacket login;
			struct loginResponse response;

			testPacket >> packetType;

			switch (packetType) {

			case GAMELOGIN:
				testPacket >> login.username;
				testPacket >> login.password;

				if (loginHandler.authenticateUser(login.username,
						login.password) == AUTH_VALID) {

					std::cout << login.username << " authenticated."
							<< std::endl;

					testPacket.clear();
					response.packetType = GAMELOGINRESPONSE;
					response.response = AUTH_VALID;
					testPacket << response.packetType << response.response;

					std::cout << "Sending to client: " << client;

					test.send(testPacket, client);

					testPacket.clear();
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
