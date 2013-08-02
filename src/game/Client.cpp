/*
 * Client.cpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */

#include "Client.hpp"
#include <iostream>
Client::Client() {

	if(this->socket.bind( sf::Socket::AnyPort )  != sf::Socket::Done )
		return;

	setPort(socket.getLocalPort());

	socket.setBlocking(false);

	std::cout << "Created socket with: " << getPort() << std::endl;
}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

unsigned short int Client::getPort() const {
	return port;
}

void Client::setPort(unsigned short int port) {
	this->port = port;
}

sf::IpAddress Client::getServerAddress() const {
	return serverAddress;
}

void Client::setServerAddress(sf::IpAddress serverAddress) {
	this->serverAddress = serverAddress;
}

unsigned short int Client::getServerPort() const {
	return serverPort;
}

void Client::setServerPort(unsigned short int serverPort) {
	this->serverPort = serverPort;
}


sf::Socket::Status Client::send( sf::Packet data) {

	return this->socket.send(data, getServerAddress(), getServerPort());

}

sf::Socket::Status Client::receive( sf::Packet *data) {

	return this->socket.receive( *data, serverAddress, serverPort);
}
