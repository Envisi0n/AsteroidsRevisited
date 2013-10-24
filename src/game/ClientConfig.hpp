/*
 * ClientConfig.hpp
 *
 *  Created on: Aug 22, 2013
 *      Author: Cam
 */

#ifndef CLIENTCONFIG_HPP_
#define CLIENTCONFIG_HPP_

#include <string>

/* List of supported config options
 *
 * Host: Ip or hostname of the server to connect to.
 * Fullscreen: true or false whether to use fullscreen
 */


class ClientConfig {
public:
	ClientConfig();
	virtual ~ClientConfig();

	void loadConfig();
	void saveConfig();

	const std::string& getServerIp() const;
	void setServerIp(const std::string& serverIp);
	bool isFullScreen() const;
	void setFullScreen(bool fullScreen);

private:

	// Hostname of server
	std::string serverIP;
	// Whether fullscreen is enabled
	bool fullScreen;
};

#endif /* CLIENTCONFIG_HPP_ */
