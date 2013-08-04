/*
 * Server.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "Server.hpp"
#include <iostream>

Server::Server(unsigned short int port) {

	for (int i = 0; i < MAXCLIENTS; i++) {

		clients[i].inUse = false;
		clients[i].ip = "0.0.0.0";
		clients[i].port = 0;

	}

	if (this->socket.bind(port) != sf::Socket::Done)
		return;

	socket.setBlocking(false);
	setPort(port);

	std::cout << "Created socket with: " << getPort() << std::endl;

}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

unsigned short int Server::getPort() const {
	return port;
}

int Server::broadcast(sf::Packet data) {

	for (int i = 0; i < MAXCLIENTS; i++) {

		if (clients[i].inUse) {

			socket.send(data, clients[i].ip, clients[i].port);

		}
	}

	return 0;

}

void Server::setPort(unsigned short int port) {
	this->port = port;
}

sf::Socket::Status Server::send(sf::Packet data, int client) {

	return socket.send(data, clients[client].ip, clients[client].port);

}

sf::Socket::Status Server::receive(sf::Packet *data, int client) {

	return socket.receive(*data, clients[client].ip, clients[client].port);
}

int Server::receive(sf::Packet* data) {

	sf::IpAddress ip;
	unsigned short int port;

	if (socket.receive(*data, ip, port) == sf::Socket::Done) {

		for (int i = 0; i < MAXCLIENTS; i++) {

			// We know this client already
			if (clients[i].inUse && clients[i].ip == ip
					&& clients[i].port == port) {
				return i;
			}

			// new client
			if (!clients[i].inUse) {
				clients[i].ip = ip;
				clients[i].port = port;
				clients[i].inUse = true;
				return i;
			}
		}
		return -1;
	}
	return -1;
}
