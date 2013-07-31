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
				testPacket.clear();
				response.packetType = GAMELOGINRESPONSE;
				switch (loginHandler.authenticateUser(login.username,
						login.password)) {

				case AUTH_VALID:

					std::cout << login.username << " authenticated."
							<< std::endl;

					response.response = AUTH_VALID;

					break;
				case AUTH_UNKNOWN_USER:

					std::cout << login.username << " invalid user."
							<< std::endl;

					response.response = AUTH_UNKNOWN_USER;

					break;

				case AUTH_INVALID_PASSWORD:

					std::cout << login.username << " invalid password."
							<< std::endl;

					response.response = AUTH_INVALID_PASSWORD;

					break;
				}

				testPacket << response.packetType << response.response;
				std::cout << "Sending to client: " << client;

				test.send(testPacket, client);
				testPacket.clear();

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
			testPacket.clear();
		}
	}

	return 0;
}
