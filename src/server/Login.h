/*
 * Login.h
 *
 *  Created on: Jul 28, 2013
 *      Author: cameron
 */

#ifndef LOGIN_H_
#define LOGIN_H_

#include <vector>
#include "User.h"

enum authenicationTypes {
	VALID,
	UNKNOWN_USER,
	INVALID_PASSWORD

};

class Login {
public:
	Login();
	virtual ~Login();

	int authenticateUser(char *username, char *password);

private:

	std::vector<User> users;
};

#endif /* LOGIN_H_ */
