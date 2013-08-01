/*
 * Login.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: cameron
 */

#include "Login.hpp"
#include <iostream>
#include <fstream>
#include "string.h"

Login::Login() {



}

Login::~Login() {



}

int Login::authenticateUser(std::string username, std::string password) {

	for (std::vector<User>::iterator it = users.begin(); it != users.end();
			++it) {

		if ((*it).getUsername() == username) {

			if ((*it).getPassword() == password) {
				return AUTH_VALID;
			} else {
				return AUTH_INVALID_PASSWORD;
			}
		}
	}
	return AUTH_UNKNOWN_USER;
}

int Login::loadDB() {

	std::ifstream db;
	User tmpuser;
	std::string line;
	char *tok;
	char *tmp;

	db.open("serverdb");
	while (db.is_open() && std::getline(db, line)) {

		if (line.length() > 0) {

			// Username
			tmp = strdup(line.c_str());
			tok = strtok(tmp, ":");

			tmpuser.setUsername(tok);

			// Password
			tok = strtok(NULL, ":");
			tmpuser.setPassword(tok);
			delete tmp;

			users.push_back(tmpuser);

		}

	}

	db.close();

	return 1;

}

int Login::saveDB() {

	std::ofstream db;

	db.open("serverdb");

	for (std::vector<User>::iterator it = users.begin(); it != users.end();
			++it) {

		std::cout << "WRITING:" << (*it).toString() << std::endl;
		db << (*it).toString() << std::endl;

	}

	db.close();

	return 1;

}

int Login::registerUser(std::string username, std::string password) {

	User tmp;

	for (std::vector<User>::iterator it = users.begin(); it != users.end();
			++it) {

		if ((*it).getUsername() == username) {
			return REG_INUSE;
		}
	}

	std::cout << "Registering user: " << username << std::endl;
	tmp.setUsername(username);
	tmp.setPassword(password);

	users.push_back(tmp);

	return REG_SUCCESS;

}
