#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
class News
{
public:
	vector<int> rates;

protected:
	string title;
	string description;
	string date;
	string average_rate = "3.0";
	string category;
	string adminUserName;
	string adminFirstName;
	string adminSecondName;
public:

	// Constructors


	// Getters
	string getTitle();
	string getDescription();
	string getDate();
	string getRate();
	string getCategory();
	string getAdminUserName();
	string getAdminFirstName();
	string getAdminSecondName();


	// Setters
	void setTitle(string title);
	void setDescription(string description);
	void setDate(string date);
	void setCategory(string category);
	void setAdminUserName(string adminUserName);
	void setAdminFirstName(string adminFirstName);
	void setAdminSecondName(string adminSecondName);
	void setAvgRate(string avg);
	void addNewRate(string rate);
	// container
	static unordered_map<string, News> News_Container;
};