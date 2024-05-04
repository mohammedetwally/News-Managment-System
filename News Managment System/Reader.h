#pragma once
#include"User.h"
#include"News.h"
#include<unordered_map>
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
	void viewLatestNews(unordered_map<string, News> newsContainer);
	void categorySearch();
	void keywordSearch();
	void searchByDate();
	void displayCategories();
	void rateNews();
	void bookmarkNews();
	void trendingNews();
	void titelSearch();
	void showPreferedNews();
};