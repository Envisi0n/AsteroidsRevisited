/*
 * User.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: cameron
 */

#include "User.h"
#include <sstream>

User::User() {
	// TODO Auto-generated constructor stub

}

User::~User() {
	// TODO Auto-generated destructor stub
}

const std::string& User::getPassword() const {
	return password;
}

void User::setPassword(const std::string& password) {
	this->password = password;
}

const std::string& User::getUsername() const {
	return username;
}

void User::setUsername(const std::string& username) {
	this->username = username;
}

std::string User::toString() {

	std::stringstream tmp;

	tmp << getUsername() << ":" << getPassword();


	return tmp.str();

}
