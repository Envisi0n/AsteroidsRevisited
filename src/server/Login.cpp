/*
 * Login.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: cameron
 */

#include "Login.h"
#include <fstream>
#include "string.h"

Login::Login() {

	std::ifstream db;
	User tmpuser;
	std::string line;
	char *tok;
	char *tmp;

	db.open("serverdb");
	if( db.is_open() ) {

		std::getline(db,line);

		// Username
		tmp = strdup( line.c_str());
		tok = strtok( tmp, ":");
		tmpuser.setUsername(tok);

		// Password
		tok = strtok( NULL, ":");
		tmpuser.setPassword(tok);
		delete tmp;

	}
}

Login::~Login() {
	std::ofstream db;

	db.open("serverdb");

	for (std::vector<User>::iterator it = users.begin(); it != users.end(); ++it) {

		db << (*it).toString() << std::endl;

	}
}

