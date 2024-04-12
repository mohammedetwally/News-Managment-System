#pragma once
#include<iostream>
#include<string>
using namespace std;
class User
{
protected:
	string user_name;
	string password;
	string first_name;
	string second_name;
	string role;

public:
	// Getter methods
	string getFirstName();
	string getSecondName();
	string getUserName();
	string getPassword();
	string getRole();


	// Setter methods
	void setUserName(string username);
	void setPassword(string pass);
	void setFirstName(string first_name);
	void setSecondName(string second_name);
	void setRole(string role);


	// Registeration methods
	void enter_first_name(string first_name, User& user);
	void enter_second_name(string second_name, User& user);
	void enter_password(string password, User& user);
	void enter_username(string username, User& user);

	// User Functionalities
	User user_register();
	void login(User user);
};
