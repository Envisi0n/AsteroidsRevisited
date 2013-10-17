/*
 * testServer.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "../shared/GameConnection.hpp"
#include "../shared/GameReliabilitySystem.hpp"
#include "../shared/GameGlobals.hpp"
#include <iostream>
#include <SFML/System.hpp>

int main(int argc, char *argv[]) {

	GameConnection test(PROTOCOL, TIMEOUT);
	GameReliabilitySystem test2;
	char buf[32];
	sf::Packet testPacket;
	sf::IpAddress ip;

	test.setAddress("127.0.0.1");
	test.setRemotePort(30001);
	test.Start(30000);
	test.Listen();

	float sendAc = 0;
	float sendRate = 30;
	int bytes = 0;
	float delta = 1.0 / 30.0f;

	while (1) {

		testPacket.clear();

		while (true) {

			if ((bytes = test.ReceivePacket(&testPacket)) == 0)
				break;

			testPacket >> buf;
			std::cout << "Received: " << buf << std::endl;
			testPacket.clear();

		}

		sendAc += delta;

		while (sendAc > 1.0f / sendRate) {
			testPacket << "2";
			test.SendPacket(testPacket);
			testPacket.clear();
			sendAc -= 1.0f / sendRate;
		}

		test.Update(0);
		std::cout << test.getReliabilitySystem().toString() << std::endl;
		sf::sleep(sf::seconds(delta));
	}
	return 0;

}
