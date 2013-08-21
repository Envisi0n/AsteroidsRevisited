/*
 * testClient.cpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */
#include "../shared/GameConnection.hpp"
#include <SFML/System.hpp>
#include <iostream>
#include "../shared/GameReliabilitySystem.hpp"

int main(int argc, char *argv[]) {

	GameConnection test(PROTOCOL, TIMEOUT);

	char buf[32];
	sf::Packet testPacket;

	testPacket << argv[1];

	test.setAddress("127.0.0.1");
	test.setRemotePort(30000);
	test.Start(30001);

	while (1) {

		test.SendPacket(testPacket);

		while (test.ReceivePacket(&testPacket) == 0) {
		}
		testPacket >> buf;
		std::cout << "Received: " << buf << std::endl;

		testPacket.clear();
		buf[0] = '1';
		buf[1] = 0;
		testPacket << buf;
		test.Update(33);
		std::cout << test.getReliabilitySystem().toString() << std::endl;
		sf::sleep(sf::milliseconds(33));
	}
	return 0;

}

