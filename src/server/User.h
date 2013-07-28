/*
 * User.h
 *
 *  Created on: Jul 28, 2013
 *      Author: cameron
 */

#ifndef USER_H_
#define USER_H_

#include <string>

class User {
public:
	User();
	virtual ~User();
	const std::string& getPassword() const;
	void setPassword(const std::string& password);
	const std::string& getUsername() const;
	void setUsername(const std::string& username);

	std::string toString();

private:
	std::string username;
	std::string password;
};

#endif /* USER_H_ */
