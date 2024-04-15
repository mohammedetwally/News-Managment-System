#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<queue>
#include<map>
using namespace std;
class News
{
protected:
	string title;
	string description;
	string date;
	string rate;
	string category;
	string adminUserName;
public:

	// Constructors
	

	// Getters
	string getTitle();
	string getDescription();
	string getDate();
	string getRate();
	string getCategory();
	string getAdminUserName();

	// Setters
	void setTitle(string title);
	void setDescription(string description);
	void setDate(string date);
	void setRate(string rate);
	void setCategory(string category);
	void setAdminUserName(string adminUserName);

	// container
	static vector<News> latestNews; // Contain news sorted with date
	static unordered_map<string,News> newsCategories; // contain a key which is category and an data which is News
	static map<tuple<string, string, string> ,News> allNews; // Contain all news with a key which is Admin's username
};