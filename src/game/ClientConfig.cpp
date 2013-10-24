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
	setFullScreen(false);
	setServerIp("127.0.0.1");

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

		// Handle each key here

		// Server address
		if (tmp == "Host:") {
			lineParser >> tmp;

			if (tmp.empty()) {
				setServerIp("127.0.0.1");
			} else {
				setServerIp(tmp);
			}
		}
		// Full screen
		else if (tmp == "Fullscreen:") {

			lineParser >> tmp;

			if (tmp.empty()) {
				setFullScreen(false);
			}
			else if( tmp == "true") {
				setFullScreen(true);
			}
			else if( tmp == "false") {
				setFullScreen(false);
			}
			else {
				setFullScreen(false);
			}
		}
		else {
			std::cout << "Invalid key: " << tmp << std::endl;
		}

	}

	config.close();

}
void ClientConfig::saveConfig() {

	std::ofstream config;

	config.open("client.cfg");

	// Write server ip
	if (getServerIp().empty()) {
		setServerIp("127.0.0.1");
	}
	config << "Host: " << getServerIp() << std::endl;
	// Write full screen
	if( isFullScreen() ) {
		config << "Fullscreen: true" << std::endl;
	}
	else {
		config << "Fullscreen: false" << std::endl;
	}

	config.close();

	std::cout << "Wrote config." << std::endl;
}

void ClientConfig::setServerIp(const std::string& serverIp) {
	serverIP = serverIp;
}

bool ClientConfig::isFullScreen() const {
	return fullScreen;
}

void ClientConfig::setFullScreen(bool fullScreen) {
	this->fullScreen = fullScreen;
}
