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

#define PROTOCOL 1
#define TIMEOUT 10

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
	virtual void Update(float deltaTime, GameReliabilitySystem & clientInstance);
	// Sends packet to pre-set destination
	virtual bool SendPacket(sf::Packet packet);
	// Sends packet to specified destination using its seq/ack system
	virtual bool SendPacket(sf::Packet packet, sf::IpAddress ipAddress, unsigned short port,
			GameReliabilitySystem & clientInstance);
	// Sends packet to pre-set destination
	virtual int ReceivePacket(sf::Packet *packet);
	// Sends packet to specified destination using its seq/ack system
	virtual int ReceivePacket(sf::Packet *packet, sf::IpAddress *ipAddress, unsigned short *port,
			GameReliabilitySystem & clientInstance);
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
	unsigned short getPort() const;
	void setPort(unsigned short port);
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
	GameReliabilitySystem& getReliabilitySystem();
	unsigned short getRemotePort() const;
	void setRemotePort(unsigned short remotePort);

protected:
	virtual void OnStart() {
	}
	virtual void OnStop() {
	}
	virtual void OnConnect() {
	}
	virtual void OnDisconnect() {
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
	unsigned short port;
	unsigned short remotePort;

	GameReliabilitySystem reliabilitySystem;
};

#endif /* GAMECONNECTION_HPP_ */
