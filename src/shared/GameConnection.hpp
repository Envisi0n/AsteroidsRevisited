/*
 * GameConnection.hpp
 *
 *  Created on: Aug 19, 2013
 *      Author: Cam
 */

#ifndef GAMECONNECTION_HPP_
#define GAMECONNECTION_HPP_

#include <SFML/Network.hpp>
#include "GameReliabilitySystem.hpp"

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

	// Operations
	bool Start(int port);
	void Stop();
	void Listen();
	void Connect(sf::IpAddress address);
	virtual void Update(float deltaTime);
	virtual bool SendPacket(sf::Packet packet);
	virtual bool SendPacket(sf::Packet packet, sf::IpAddress, int port);
	// Utility

	bool isConnected() const;
	bool isConnecting() const;
	bool isConnectFailed() const;
	bool isListening() const;

	// Getters/Setters
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

protected:
	virtual void OnStart() {
	}
	virtual void OnStop() {
	}
	virtual void OnConnect() {
	}
	virtual void OnDisconnect() {
	}

	void WriteInteger(unsigned char * data, unsigned int value) {
		data[0] = (unsigned char) (value >> 24);
		data[1] = (unsigned char) ((value >> 16) & 0xFF);
		data[2] = (unsigned char) ((value >> 8) & 0xFF);
		data[3] = (unsigned char) (value & 0xFF);
	}

	void WriteHeader(unsigned char * header, unsigned int protocol, unsigned int sequence,
			unsigned int ack, unsigned int ack_bits) {
		WriteInteger(header, protocol);
		WriteInteger(header + 4, sequence);
		WriteInteger(header + 8, ack);
		WriteInteger(header + 12, ack_bits);
	}

	void ReadInteger(const unsigned char * data, unsigned int & value) {
		value = (((unsigned int) data[0] << 24) | ((unsigned int) data[1] << 16)
				| ((unsigned int) data[2] << 8) | ((unsigned int) data[3]));
	}

	void ReadHeader(const unsigned char * header, unsigned int & sequence,
			unsigned int & ack, unsigned int & ack_bits) {
		ReadInteger(header, sequence);
		ReadInteger(header + 4, ack);
		ReadInteger(header + 8, ack_bits);
	}

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

	GameReliabilitySystem reliabilitySystem;
};

#endif /* GAMECONNECTION_HPP_ */
