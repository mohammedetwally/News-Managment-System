#include<iostream>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include<vector>
#include"News.h"
#include "Reader.h"
#include"Test.h"
#include "Menus.h"
using namespace std;
map<string, User> Reader::reader_container;

void Reader::edit_profile()
{
	//this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
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
	cin.ignore();
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
	reader_container[this->getUserName()] = *this;
	Menus::readerMenu(*this);

}

void Reader::view_proile()
{
	cout << "\t\t\t\t\t\tyour data\n";
	cout << "\nCurrent User Name: " << this->user_name << endl;
	cout << "Current Password: " << this->password << endl;
	cout << "Current First Name: " << this->first_name << endl;
	cout << "Current Second Name: " << this->second_name << endl;

	Menus::readerMenu(*this);

}

void Reader::viewLatestNews()
{
	// See New News (:
	system("cls");
	for (int i = News::latestNews.size() - 1; i >= 0; i--) {
		cout << "\n\nTitle : " << News::latestNews[i].getTitle() << endl;
		cout << News::latestNews[i].getDescription() << endl;
		cout << "                                                         Date : " << News::latestNews[i].getDate() << endl;
	flag:
		cout << "\n\nPlease enter rate for this news: ";
		string rate;
		cin >> rate;
		if(Test::rate_test(rate))
			News::latestNews[i].addNewRate(rate);
		else
		{
			cout << "\nInvalid Choice .... Please Try Again\n";
			goto flag;
		}
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
	Menus::readerMenu(*this);
}

void Reader::categorySearch()
{
	// Allow User to Search By Categories
	cout << "enter the category you want \n";
	string category;
	cin.ignore();
	getline(cin, category);
	if (News::newsCategories.find(category) != News::newsCategories.end())
	{
		for (auto news : News::newsCategories[category])
		{
				cout << "news title is  : " << news.getTitle() << endl<<endl;
				cout << "news discription is : " << news.getDescription() <<endl<< endl;
				cout << "news date is : " << news.getDate() << endl<<endl;
				cout << "written by : " << news.getAdminUserName() << endl<<endl;
				cout << "\t\t\t\t\t\t_____________________________________\t\t\t\t\t";
				cout << endl;
		}
	}
	else
	{
		cout << "invalid category \n1-return to main menu \n2-try again\n" << endl;
	}
flag2004:
		string choice;
		cin >> choice;
		if (choice.length()==1&&choice=="1")
		{
			Menus::readerMenu(*this);
		}
		else if (choice.length() == 1 && choice == "2")
		{
			categorySearch();
		}
		else
		{
			cout << "invalid value \n1-return to main menu\n2-try again\n\n";
			goto flag2004;
		}
}

void Reader::keywordSearch()
{
	// Allow User to Search By KeyWords
}

void Reader::displayCategories()
{
}

void Reader::rateNews()
{
}

void Reader::bookmarkNews()
{
}

void Reader::trendingNews()
{
}

void Reader::titelSearch()
{
}
