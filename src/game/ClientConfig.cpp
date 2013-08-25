/*
 * ClientConfig.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: Cam
 */

#include "ClientConfig.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

ClientConfig::ClientConfig() {
	// TODO Auto-generated constructor stub

}

ClientConfig::~ClientConfig() {
	// TODO Auto-generated destructor stub
}

const std::string& ClientConfig::getServerIp() const {
	return serverIP;
}

void ClientConfig::loadConfig() {

	std::ifstream config;
	std::string token, tmp;

	config.open("client.cfg");

	while (config.is_open() && std::getline(config, token)) {

		std::stringstream lineParser(token);
		lineParser >> tmp;

		if (tmp == "Host:") {
			lineParser >> tmp;

			if (tmp.empty()) {
				setServerIp("127.0.0.1");
			} else {
				setServerIp(tmp);
			}
		} else {
			std::cout << "Invalid key: " << tmp << std::endl;
		}

	}

	config.close();

}
void ClientConfig::saveConfig() {

	std::ofstream config;

	config.open("client.cfg");

	// Write server ip
	if( getServerIp().empty()) {
		setServerIp("127.0.0.1");
	}
	config << "Host: " << getServerIp() << std::endl;

	config.close();

	std::cout << "Wrote config." << std::endl;
}

void ClientConfig::setServerIp(const std::string& serverIp) {
	serverIP = serverIp;
}
