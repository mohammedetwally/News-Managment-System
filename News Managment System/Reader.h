#pragma once
#include"User.h"
class Reader : public User
{
public:
	// Constructors
	Reader() : User() {};
	Reader(const User& user) : User(user) {};

	// Containers
	static map<string, User> reader_container;

	// Reader Functionalities
	void edit_profile();
	void view_proile();
	void viewLatestNews();
	void categorySearch();
	void keywordSearch();
};
