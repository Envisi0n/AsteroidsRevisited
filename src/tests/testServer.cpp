/*
 * testServer.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "../shared/GameConnection.hpp"
#include "../shared/GameReliabilitySystem.hpp"
#include <iostream>
#include <SFML/System.hpp>

int main(int argc, char *argv[]) {

	GameConnection test(PROTOCOL, TIMEOUT);
	GameReliabilitySystem test2;
	char buf[32];
	sf::Packet testPacket;
	sf::IpAddress ip;
	unsigned short port;
	testPacket << argv[1];

	test.setAddress("127.0.0.1");
	test.setPort(30001);
	test.Start(30000);

	while (1) {
	//	std::cout << "waiting for packet" << std::endl;
		while (test.ReceivePacket(&testPacket) == 0) {

		}
		testPacket >> buf;

		std::cout << "Received: " << buf << std::endl;
		testPacket.clear();
		testPacket << buf;

		test.SendPacket(testPacket);

		test.Update(33);

		std::cout << test.getReliabilitySystem().toString() << std::endl;

		buf[0] = '1';
		buf[1] = 0;

		sf::sleep(sf::milliseconds(33));
	}
	return 0;

}
