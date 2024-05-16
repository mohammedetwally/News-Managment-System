#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "User.h"
#include "Admin.h"
#include "Reader.h"
#include "News.h"

using namespace std;

class Test
{
public:
	static bool names_test(string name);
	static bool space_test(string& word);
	static int password_strength(string password);
	static User adminOrReader(User user);
	static bool adminValidation(Admin admin, string login_password, string login_username);
	static bool readerValidation(Reader reader, string login_password, string login_username);
	static bool user_check(User& user);
	static bool title_description_Test(string title_description);
	static bool category_test(string category);
	static bool rate_test(string rate);
	static bool compareByDate(pair<string, News> a, pair<string, News> b);
	static bool isDate(string inputStr);
	static string extractDate(string fullDate);
	static bool testComment(string comment);
};