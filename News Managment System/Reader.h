#pragma once
#include"User.h"
class Reader : public User
{
public:
	Reader(const User& user) : User(user) {};
	void edit_profile(Reader reader);
	void viewLatestNews();
	void categorySearch();
	void keywordSearch();
};
