/*
 * Server.cpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#include "Server.hpp"
#include <iostream>
Server::Server(unsigned short int port) {
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

void Server::setPort(unsigned short int port) {
	this->port = port;
}

sf::Socket::Status Server::send( sf::Packet data, int client) {

	return this->socket.send(data, clients[client].ip, clients[client].port);

}

sf::Socket::Status Server::receive( sf::Packet *data, int client) {

	return this->socket.receive( *data, clients[client].ip, clients[client].port );
}
