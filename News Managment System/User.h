#pragma once
#include<iostream>
#include<string>
# include<map>
#include<set>
using namespace std;
class User
{
protected:
	string user_name;
	string password;
	string first_name;
	string second_name;
	string role;
	set<string>preferredCategories;

public:
	User() {};
	// Getter methods
	string getFirstName();
	string getSecondName();
	string getUserName();
	string getPassword();
	string getRole();

	// containers

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
	void preferred_categories(User& user);

	// User Functionalities
	void user_register();
	void login(User user);
};
