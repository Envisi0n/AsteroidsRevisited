/*

 * Server.hpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "../shared/GameConnection.hpp"

#define MAXCLIENTS 16

struct clientInfo {
	sf::IpAddress ip;
	unsigned short int port;
	bool inUse;
	int state;
	GameReliabilitySystem stats;
};

class ServerConnection {
public:
	ServerConnection();
	virtual ~ServerConnection();

	// Sends to a specific client
	bool send(sf::Packet data, int client);
	// Receives from a specific client
	int receive(sf::Packet *data, int client);
	// Sends to all clients
	int broadcast(sf::Packet data);
	// Receives a packet from any source
	int receive(sf::Packet *data);
	// Disconnect a client
	void disconnectClient(int client);
	void disconnectAll();

	// List clients
	void printClients();

	void printStats();
	void update(float delta);

	sf::IpAddress getClientIp(int client);
	short getClientPort(int client);
	bool isClientConnected(int client);

private:

	GameConnection connection;

	struct clientInfo clients[MAXCLIENTS];

};

#endif /* SERVER_HPP_ */
