/*
 * Server.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "ServerConnection.hpp"
#include <iostream>
#include "../shared/Net_shared.hpp"
#include "../shared/GameGlobals.hpp"

ServerConnection::ServerConnection() :
		connection(PROTOCOL, TIMEOUT) {

	for (int i = 0; i < MAXCLIENTS; i++) {

		clients[i].inUse = false;
		clients[i].ip = "0.0.0.0";
		clients[i].port = 0;
		clients[i].stats.Reset();

	}

	connection.setRemotePort(CLIENT_PORT);
	connection.Start(SERVER_PORT);

}

ServerConnection::~ServerConnection() {
	// TODO Auto-generated destructor stub
}

int ServerConnection::broadcast(sf::Packet data) {

	for (int i = 0; i < MAXCLIENTS; i++) {

		if (clients[i].inUse) {

			connection.SendPacket(data, clients[i].ip, clients[i].port,
					clients[i].stats);

		}
	}

	return 0;

}

void ServerConnection::printStats() {

	for (int i = 0; i < MAXCLIENTS; i++) {

		if (clients[i].inUse) {

			std::cout << clients[i].stats.toString() << std::endl;

		}
	}

}

void ServerConnection::disconnectClient(int client) {

	sf::Packet disconnectPacket;
	genericPacket data;

	if (client > MAXCLIENTS) {
		return;
	}

	data.packetType = DISCONNECT;

	disconnectPacket << data;

	send(disconnectPacket, client);

	clients[client].ip = "0.0.0.0";
	clients[client].port = 0;
	clients[client].inUse = false;
	clients[client].stats.Reset();

}

void ServerConnection::disconnectAll() {

	for (int i = 0; i < MAXCLIENTS; i++) {
		disconnectClient(i);
	}

}

bool ServerConnection::send(sf::Packet data, int client) {

	std::cout << "Sending to: " << clients[client].ip << ":"
			<< clients[client].port << std::endl;

	return connection.SendPacket(data, clients[client].ip, clients[client].port,
			clients[client].stats);

}

int ServerConnection::receive(sf::Packet *data, int client) {

	return connection.ReceivePacket(data, &clients[client].ip,
			&clients[client].port, clients[client].stats);
}

int ServerConnection::receive(sf::Packet* data) {

	sf::IpAddress ip;
	unsigned short int port;
	int bytes;
	if ((bytes = connection.ReceivePacket(data, &ip, &port)) > 0) {

		for (int i = 0; i < MAXCLIENTS; i++) {

			// We know this client already
			if (clients[i].inUse && clients[i].ip == ip
					&& clients[i].port == port) {
				connection.ProcessRecieve(data, bytes, clients[i].stats);
				return i;
			}

			// new client
			if (!clients[i].inUse) {
				clients[i].ip = ip;
				clients[i].port = port;
				clients[i].inUse = true;
				connection.ProcessRecieve(data, bytes, clients[i].stats);
				return i;
			}
		}
		return -1;
	}
	return -1;
}

void ServerConnection::update(float delta) {

	for (int i = 0; i < MAXCLIENTS; i++) {
		clients[i].stats.Update(delta);
	}

}

sf::IpAddress ServerConnection::getClientIp(int client) {
	return clients[client].ip;
}

short ServerConnection::getClientPort(int client) {
	return clients[client].port;
}

bool ServerConnection::isClientConnected(int client) {
	return clients[client].inUse;
}
