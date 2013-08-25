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
#include "../shared/GameGlobals.hpp"

int main(int argc, char *argv[]) {

	GameConnection test(PROTOCOL, TIMEOUT);

	char buf[32];
	sf::Packet testPacket;

	float sendAc = 0;
	float sendRate = 30;
	int bytes = 0;
	float delta = 1.0/30.0f;

	test.setAddress("127.0.0.1");
	test.setRemotePort(30000);
	test.Start(30001);
	test.Connect("127.0.0.1");

	while (1) {

		sendAc += delta;

		while (sendAc > 1.0f / sendRate) {
			testPacket << "1";
			test.SendPacket(testPacket);
			testPacket.clear();
			sendAc -= 1.0f / sendRate;
		}

		testPacket.clear();

		while (true) {

			if ((bytes = test.ReceivePacket(&testPacket)) == 0)
				break;

			testPacket >> buf;
			std::cout << "Received: " << buf << std::endl;
			testPacket.clear();

		}
		test.Update(delta);
		std::cout << test.getReliabilitySystem().toString() << std::endl;
		sf::sleep(sf::seconds(delta));
	}
	return 0;

}

