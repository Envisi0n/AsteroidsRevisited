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
			struct genericPacket response;

			testPacket >> packetType;

			switch (packetType) {

			case GAMELOGIN:
				testPacket >> login.username;
				testPacket >> login.password;
				testPacket.clear();

				switch (loginHandler.authenticateUser(login.username,
						login.password)) {

				case AUTH_VALID:

					std::cout << login.username << " authenticated."
							<< std::endl;

					response.packetType = LOGIN_AUTH_VALID;

					break;
				case AUTH_UNKNOWN_USER:

					std::cout << login.username << " invalid user."
							<< std::endl;

					response.packetType = LOGIN_AUTH_UNKNOWN_USER;

					break;

				case AUTH_INVALID_PASSWORD:

					std::cout << login.username << " invalid password."
							<< std::endl;

					response.packetType = LOGIN_AUTH_INVALID_PASSWORD;

					break;
				}

				testPacket << response.packetType;
				std::cout << "Sending to client: " << client;

				test.send(testPacket, client);
				testPacket.clear();

				break;

			case GAMEREGISTER:
				testPacket >> login.username;
				testPacket >> login.password;
				testPacket.clear();

				switch (loginHandler.registerUser(login.username,
						login.password)) {
				case REG_SUCCESS:
					std::cout << login.username << " " << "registered."
							<< std::endl;
					response.packetType = LOGIN_REG_SUCCESS;
					break;
				case REG_INUSE:
					std::cout << login.username << " " << "already in use."
							<< std::endl;
					response.packetType = LOGIN_REG_INUSE;
					break;
				}

				testPacket << response.packetType;
				std::cout << "Sending to client: " << client;

				test.send(testPacket, client);
				testPacket.clear();
				break;

			}
			testPacket.clear();
		}
	}

	return 0;
}
