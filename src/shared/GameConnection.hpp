/*
 * GameConnection.hpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 */

#ifndef GAMECONNECTION_HPP_
#define GAMECONNECTION_HPP_

#include <SFML/Network.hpp>

class GameConnection {
public:

	enum Mode {
		None, Client, Server
	};

	GameConnection();
	virtual ~GameConnection();

private:
	enum State {
		Disconnected, Listening, Connecting, ConnectFail, Connected
	};

	unsigned int protocolId;
	float timeout;

	bool running;
	Mode mode;
	State state;
	sf::UdpSocket socket;
	float timeoutAccumulator;
	sf::IpAddress address;
	int port;
};

#endif /* GAMECONNECTION_HPP_ */
