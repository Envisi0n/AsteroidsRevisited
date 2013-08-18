/*
 * Net_shared.hpp
 *
 *  Created on: Jul 11, 2013
 *      Author: cameron
 */

#ifndef NET_SHARED_HPP_
#define NET_SHARED_HPP_
#include <SFML/Network.hpp>
#include "World.hpp"

#define SERVER_PORT 30000

enum PacketTypes{

	GAMELOGIN,
	GAMEREGISTER,

	LOGIN_AUTH_VALID,
	LOGIN_AUTH_UNKNOWN_USER,
	LOGIN_AUTH_INVALID_PASSWORD,
	LOGIN_REG_SUCCESS,
	LOGIN_REG_INUSE,

	HEARTBEAT,
	DISCONNECT,
	CLIENT_UPDATE,
	SERVER_UPDATE,

};

enum loginTypes {
	LOG_REGISTER,
	LOG_LOGIN,
};


struct genericPacket {
	short packetType;

};


// Used for both registering and login
struct loginPacket {
	short packetType;
	char username[32];
	char password[32];
};

struct loginResponse {
	short packetType;
	short response;
};

struct serverUpdatePacket {
	short packetType;
	World world;
};


class GamePacket {

public:

	GamePacket();
	virtual ~GamePacket();

	sf::Packet toSFPacket();

private:
	int seq;
	int type;

};


sf::Packet& operator <<(sf::Packet& packet, const genericPacket& connect);
sf::Packet& operator >>(sf::Packet& packet, genericPacket& connect);

sf::Packet& operator <<(sf::Packet& packet, const loginPacket& login);
sf::Packet& operator >>(sf::Packet& packet, loginPacket& login);

sf::Packet& operator <<(sf::Packet& packet, const loginResponse& login);
sf::Packet& operator >>(sf::Packet& packet, loginResponse& login);



#endif /* NET_SHARED_HPP_ */
