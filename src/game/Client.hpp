/*
 * Client.hpp
 *
 *  Created on: May 9, 2013
 *      Author: cam
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <SFML/Network.hpp>

class Client {
public:
	Client();
	virtual ~Client();
	unsigned short int getPort() const;
	void setPort(unsigned short int port);
	sf::IpAddress getServerAddress() const;
	void setServerAddress(sf::IpAddress serverAddress);
	unsigned short int getServerPort() const;
	void setServerPort(unsigned short int serverPort);


	sf::Socket::Status send( sf::Packet data );
	sf::Socket::Status receive( sf::Packet *data);
private:

	sf::UdpSocket socket;
	unsigned short int port;
	sf::IpAddress serverAddress;
	unsigned short int serverPort;

};

#endif /* CLIENT_HPP_ */
