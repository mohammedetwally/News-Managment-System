#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include <ctime>
#include<vector>
#include "Admin.h"
#include"Test.h"
#include "Menus.h"
#include"News.h"
map<string, User> Admin::admin_container;
vector <News> News::latestNews;
map<tuple<string, string, string>, News> News::allNews;
unordered_map <string, News>  News::newsCategories;
// For Editing Admin's Exsit Data
void Admin::editProfile()
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
	system("cls");
	cout << "\nEditing Admin Profile: \n";

	// Display current profile information
	cout << "\nCurrent User Name: " << this->user_name << endl;
	cout << "Current Password: " << this->password << endl;
	cout << "Current First Name: " << this->first_name << endl;
	cout << "Current Second Name: " << this->second_name << endl;


	// Prompt user for new profile information
	cout << "Edit Your Data :\n--------------------------------------------------------------------------------------------\n\n";
	// Edit Password
flag:
	string password;
	string confirmation_pass;
	cout << "Enter new Password: ";
	cin.ignore();
	getline(cin, password);
	enter_password(password, *this);
	cout << "\nConfirm your password: ";
	getline(cin, confirmation_pass);
	if (password == confirmation_pass)
	{

		// Check Password Strength 

		string check;
		int strength = Test::password_strength(password);
		if (strength < 8)
		{
		flag9:
			cout << "\nWeak Password !!\n\n1 -> Enter a secure password\n2 -> continue\n";
			cout << "\nEnter your choice: ";
			cin >> check;
			cin.ignore();
			if (check == "1")
			{
				goto flag;
			}
			else if (check == "2")
			{
				// skip
			}
			else
			{
				cout << "Invalide choice .... Please Try Again";
				goto flag9;
			}
		}

		else if (strength >= 8 && strength < 10)
		{
		flag8:
			cout << "\nModerate Password !!\n\n1 -> Enter a secure password\n2 -> continue\n";
			cout << "\nEnter your choice: ";
			cin >> check;
			if (check == "1")
			{
				goto flag;
			}
			else if (check == "2")
			{
				// skip
			}
			else
			{
				cout << "Invalide choice .... Please Try Again";
				goto flag8;
			}
		}

		else if (strength >= 10)
		{
			cout << "\nStrong Password !!\n";
		}
	}
	else
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
		cout << "\nPassword is not matching !!\n";
		goto flag;
	}
	// Edit FirstName
	string firstName;
	cout << "Enter new First Name: ";
	//cin.ignore();
	getline(cin, firstName);
	enter_first_name(firstName, *this);

	// Edit SecondName
	string secondName;
	cout << "Enter new Second Name: ";
	getline(cin, secondName);
	enter_second_name(secondName, *this);


	// Display confirmation message
	cout << "\n*********************************************************** Profile Updated Successfully **********************************************************\n";
	cout << "\nUpdated User Name: " << this->user_name << endl;
	cout << "Updated Password: " << this->password << endl;
	cout << "Updated First Name: " << this->first_name << endl;
	cout << "Updated Second Name: " << this->second_name << endl;
	admin_container[this->getUserName()] = *this;
	Menus::adminMenu(*this);
}

void Admin::view_proile()
{

	// Display current profile information
	cout << "\t\t\t\t\t\tyour data\n";
	cout << "\nUpdated User Name: " << this->user_name << endl;
	cout << "Updated Password: " << this->password << endl;
	cout << "Updated First Name: " << this->first_name << endl;
	cout << "Updated Second Name: " << this->second_name << endl;
	Menus::adminMenu(*this);
}

void Admin::addNews()
{
	// Adds The Lastest News
	News news;
	string title;
	string description;
	string category;
	system("cls");
	cout << "\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t              Add News             " << endl;
	cout << "\t\t\t\t\t\t===================================\n\n" << endl;
	cout << "Please Enter News Data:\n\n";
	
	// Title Entery
flag:
	cout << "News Title: ";
	cin.ignore();
	getline(cin,title);
	if (Test::title_description_Test(title))
		news.setTitle(title);
	else
	{
		cout << "\nInvalid Title .... Please Try Again\n";
		goto flag;
	}

	// Description Entery
flag01:
	cout << "News Description: ";
	getline(cin, description);
	if (Test::title_description_Test(description))
		news.setDescription(description);
	else
	{
		cout << "\nInvalid Description .... Please Try Again\n";
		goto flag01;
	}

	// Category Entery
flag02:
	cout << "News Category: ";
	getline(cin, category);
	if (Test::category_test(category))
		news.setCategory(category);
	else
	{
		cout << "\nInvalid Category .... Please Try Again\n";
		goto flag02;
	}

	// Set Date With Real Time

	news.setDate(Menus::getCurrentDate());
	cout << "Adding date: " << news.getDate() << endl;


	// Set Admin UserName
	news.setAdminUserName(user_name);

	cout << "\n\nNews Data: \n\n";
	cout << "Admin's UserName: " << news.getAdminUserName();
	cout << "\nNews Title: " << news.getTitle();
	cout << "\nNews Description: " << news.getDescription();
	cout << "\nNews Category: " << news.getCategory();
	cout << "\nNews Date: " << news.getDate() << endl;

	//cout << "1 -> Submit News\n2 -> Edit News\n3 -> Don't Save";

	// Push in vector
	News::latestNews.push_back(news);

	// Push in map
	pair<tuple<string, string, string>, News> keyValue = make_pair(make_tuple(news.getAdminUserName(), news.getTitle(), news.getDescription()), news);
	News::allNews.insert(keyValue);

	// Push in Hash Table
	News::newsCategories.emplace(news.getCategory(), news);

flag03:
	cout << "\n\n1 -> Back to Admin Menu\n2 -> Add Another News\n";
	string choose;
	cin >> choose;
	if (choose == "1")
		Menus::adminMenu(*this);
	else if (choose == "2")
		this->addNews();
	else
	{
		cout << "\nInvalid Choose .... Please Try Again\n";
		goto flag03;
	}
}

void Admin::removeNews()
{
	/// Remove News
}

void Admin::viewNewsArticles() {
	// view news articles
}

void Admin::rateTitle()
{
	// Put a Rate for Each Title
}

void Admin::addCategories() {
	// manage categories
}

void Admin::editNews()
{
	// to update or edit news
}
