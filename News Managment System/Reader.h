#pragma once
#include "User.h"
#include "News.h"
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>

class Reader : public User
{
public:
	// Constructors
	Reader() : User() {};
	Reader(const User& user) : User(user) {};

	// Containers
	static map<string, Reader> reader_container;
	static map<News, stack<string>> commentsMap;
	vector <News*> bookmarking_container;
	
	// Reader Functionalities
	// Reader data
	void edit_profile();
	void view_profile();
	
	// Viewing news
	bool displayNewsArticle(News news);
	void viewLatestNews();
	void trendingNews();
	void showPreferredNews();
	void viewBookmarkedNews();
	void notifications();
	
	// Searching for news
	void titleSearch();
	void keywordSearch();
	void categorySearch();
	void searchByDate();
	
	// Extra news functionalities
	void displayNewsWithComments(News news);
	void comment(News news);
	void rateNews(News& news);
	void bookmarkNews(News* news);
	void removeAllBookmarkedNewsFromNewsContainer();
};