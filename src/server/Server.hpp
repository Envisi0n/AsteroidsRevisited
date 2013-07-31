/*

 * Server.hpp
 *
 *  Created on: May 10, 2013
 *      Author: cam
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <SFML/Network.hpp>

#define MAXCLIENTS 2

struct clientInfo {
	sf::IpAddress ip;
	unsigned short int port;
	bool inUse;
};

class Server {
public:
	Server( unsigned short int port);
	virtual ~Server();

	sf::Socket::Status send(sf::Packet data, int client);
	sf::Socket::Status receive(sf::Packet *data, int client);
	int receive(sf::Packet *data);
	unsigned short int getPort() const;
	void setPort(unsigned short int port);

private:
	sf::UdpSocket socket;
	unsigned short int port;

	struct clientInfo clients[MAXCLIENTS];

};

#endif /* SERVER_HPP_ */
