/*
 * ClientConfig.hpp
 *
 *  Created on: Aug 22, 2013
 *      Author: Cam
 */

#ifndef CLIENTCONFIG_HPP_
#define CLIENTCONFIG_HPP_

#include <string>

class ClientConfig {
public:
	ClientConfig();
	virtual ~ClientConfig();

	void loadConfig();
	void saveConfig();

	const std::string& getServerIp() const;
	void setServerIp(const std::string& serverIp);

private:
	std::string serverIP;
};

#endif /* CLIENTCONFIG_HPP_ */
