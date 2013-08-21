/*
 * testClient.cpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */
#include "../shared/GameConnection.hpp"

#include <iostream>

int main(int argc, char *argv[]) {

	GameConnection test(PROTOCOL, TIMEOUT);
	char buf[32];
	sf::Packet testPacket;

	testPacket << argv[1];

	test.setAddress("127.0.0.1");
	test.setPort(30001);

	test.SendPacket(testPacket);

	if (test.ReceivePacket(&testPacket) > 0) {

		testPacket >> buf;

		std::cout << "Received: " << buf << std::endl;

	}

	return 0;

}

