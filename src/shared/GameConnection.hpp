/*
 * GameConnection.hpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 */

#ifndef GAMECONNECTION_HPP_
#define GAMECONNECTION_HPP_

#include <SFML/Network.hpp>

enum Mode {
	None, Client, Server
};

enum State {
	Disconnected, Listening, Connecting, ConnectFail, Connected
};

class GameConnection {
public:

	GameConnection(unsigned int protocolId, float timeout);
	virtual ~GameConnection();

	sf::IpAddress getAddress() const;
	void setAddress(sf::IpAddress address);
	Mode getMode() const;
	void setMode(Mode mode);
	int getPort() const;
	void setPort(int port);
	unsigned int getProtocolId() const;
	void setProtocolId(unsigned int protocolId);
	bool isRunning() const;
	void setRunning(bool running);
	State getState() const;
	void setState(State state);
	float getTimeout() const;
	void setTimeout(float timeout);
	float getTimeoutAccumulator() const;
	void setTimeoutAccumulator(float timeoutAccumulator);

private:

	void ClearData();

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
