#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

class News
{
protected:
	string title;
	string description;
	string date;
	string category;
	string adminUserName;
	string adminFirstName;
	string adminSecondName;
	float average_rate = 3;
	set<string> spamSet;

public:
	// Constructors
	bool operator<(const News& other) const {
		return this->title < other.title;
	}

	// data members
	bool bookmarkedOrNo = false;
	float news_rate = 2.5;


	// container
	static unordered_map<string, News> News_Container;
	map<string, float>newsRates;//for easy search ,override,updates


	// Getters
	string getTitle();
	string getDescription();
	string getDate();
	float getRate();
	string getCategory();
	string getAdminUserName();
	string getAdminFirstName();
	string getAdminSecondName();
	set<string> getSpamSet();


	// Setters
	void setTitle(string title);
	void setDescription(string description);
	void setDate(string date);
	void setCategory(string category);
	void setAdminUserName(string adminUserName);
	void setAdminFirstName(string adminFirstName);
	void setAdminSecondName(string adminSecondName);
	void setAvgRate(float avg);
	void addNewRate(string rate);
	void addSpamSet(string name);
	void addUserToSpamSet(string name);
	
	// Functionalities
	void calcRate();
};