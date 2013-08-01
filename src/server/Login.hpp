/*
 * Login.h
 *
 *  Created on: Jul 28, 2013
 *      Author: cameron
 */

#ifndef LOGIN_H_
#define LOGIN_H_

#include <vector>
#include <string>
#include "User.hpp"

enum authenticationTypes {
	AUTH_VALID,
	AUTH_UNKNOWN_USER,
	AUTH_INVALID_PASSWORD,
	REG_SUCCESS,
	REG_INUSE,

};

class Login {
public:
	Login();
	virtual ~Login();

	int loadDB();
	int saveDB();
	int authenticateUser(std::string username, std::string password);
	int registerUser(std::string username, std::string password);

private:

	std::vector<User> users;
};

#endif /* LOGIN_H_ */
