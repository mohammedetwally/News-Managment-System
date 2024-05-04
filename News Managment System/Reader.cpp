#include<iostream>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include<vector>
#include<algorithm>
#include<string>
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
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
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

void Reader::viewLatestNews(unordered_map<string, News> newsContainer)
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");

	int news_to_view{};
	int i = 0;
	vector<pair<string, News>> newsVector(newsContainer.begin(), newsContainer.end());

	sort(newsVector.begin(), newsVector.end(), Test::compareByDate);
	for (auto pair = newsVector.rbegin(); pair != newsVector.rend(); ++pair)
	{
		cout << "\n" << i + 1 << ": " << pair->second.getTitle() << endl;
		i++;
	}
	sort(newsVector.begin(), newsVector.end(), Test::compareByDate);

	cout << "\nEnter the number of the article you want to view: ";
	cin >> news_to_view;
	cin.ignore(); 
	if (news_to_view > newsVector.size() || news_to_view < 0)
	{
		cout << "Invalid Choice .... Please try again";
		viewLatestNews(newsContainer);
	}
	else
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		system("cls");
		cout << "\n\nTitle : " << newsVector[newsVector.size()-news_to_view].second.getTitle() << endl;
		cout << newsVector[newsVector.size() - news_to_view].second.getDescription() << endl;
		cout << endl << newsVector[newsVector.size() - news_to_view].second.getCategory() << endl;
		cout << "                                                         Date : " << newsVector[newsVector.size() - news_to_view].second.getDate() << endl;
		cout << "This news Published by: " << newsVector[newsVector.size() - news_to_view].second.getAdminFirstName() + " " + newsVector[newsVector.size() - news_to_view].second.getAdminSecondName() << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------\n";
	}

flag111:
	cout << "\n\n1 -> Back to News Menu\n2 -> Back to your Menu\n\nEnter your choice: ";
	string choice;
	cin >> choice;
	if (choice == "1")
	{
		viewLatestNews(newsContainer);
	}
	else if (choice == "2")
	{
		Menus::readerMenu(*this);
	}
	else
	{
		cout << "\nInvalid Choice .... Please try again";
		goto flag111;
	}

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	Menus::readerMenu(*this);
}

void Reader::categorySearch()
{
	// Allow User to Search By Categories
	cout << "enter the category you want \n";
	string category;
	cin.ignore();
	getline(cin, category);
	bool check = false;//to check whether the container is exist or not
	int counter = 1;
	unordered_map<string, News>::iterator it = News::News_Container.begin();//hold mathes search
	for (auto news : News::News_Container)
	{
		if (news.second.getCategory() == category)
		{
			cout << counter << " - ";
			cout << "news title is  : " << news.second.getTitle() << endl << endl;
			check = true;//you find it
			counter++;

		}
	}
	if (check)
	{
	flag1:
		cout << "enter the nember of news you want to see\n\n";
		int choose;
		cin >> choose;
		if (choose > counter || choose < 1)
		{
			cout << "inalid value please try again\n";
			goto flag1;
		}
		else
		{
			advance(it, choose - 1);
			cout << "title : " << it->second.getTitle() << endl;
			cout << "discription : " << it->second.getDescription() << endl;
			cout << "rate : " << it->second.getRate() << endl;
			cout << "data : " << it->second.getDate() << endl;
			cout << "written by : " << it->second.getAdminUserName() << endl << endl;
		}
	}
	else if (!check)
	{
		cout << "invalid category \n1-return to main menu \n2-try again\n" << endl;
	flag2004:
		string choice;
		cin >> choice;
		if (choice.length() == 1 && choice == "1")
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
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
	Menus::readerMenu(*this);

}

void Reader::showPreferedNews()
{
	vector<string>prefered;
	for (auto i : preferredCategories)
	{
		prefered.push_back(i);

	}
	unordered_map<string, News>::iterator it = News::News_Container.begin();
	for (it; it != News::News_Container.end(); it++)
	{
		if (it->second.getCategory() == prefered[0] || it->second.getCategory() == prefered[1] || it->second.getCategory() == prefered[2])
		{
			cout << "title : " << it->second.getTitle() << endl;
			cout << "discription : " << it->second.getDescription() << endl;
			cout << "rate : " << it->second.getRate() << endl;
			cout << "data : " << it->second.getDate() << endl;
			cout << "written by : " << it->second.getAdminUserName() << endl << endl;
			cout << "\t\t\t\t\t\========================================================\t\t\t\t\t\t\n";
		}
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
	Menus::readerMenu(*this);
}


void Reader::keywordSearch()
{
	// Allow User to Search By KeyWords
}

void Reader::searchByDate() {
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	string date;
	bool validDate = false;
	while (!validDate) {
		cout << "Note that the date format is \"YYYY-MM-DD\"\n";
		cout << "Enter the date of the articles you want to display: ";
		cin >> date;
		if (Test::isDate(date)) {
			validDate = true;
		}
		else {
			cout << "Invalid Date .... Please try again\n";
			validDate = false;
		}
	}
flag_display:
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	vector<News> News_To_Display;
	// Search for articles by date
	int i = 0;
	for (auto view : News::News_Container) {
		if (Test::extractDate(view.second.getDate()) == date) {
			cout << i + 1 << ": " << view.second.getTitle() << endl;
			News_To_Display.push_back(view.second);
			i++;
		}
	}
	int display;
	while (true) {
		cout << "\nEnter the number of the news you want to display: ";
		cin >> display;
		if (display > 0 && display < News::News_Container.size()) {
			break;
		}
		else {
			cout << "Invalid Choice. Please try again.\n";
		}
	}
	display--;
	// Display selected news
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	cout << "\nTitle: " << News_To_Display[display].getTitle() << endl;
	cout << News_To_Display[display].getDescription() << endl;
	cout << "\nCategory: " << News_To_Display[display].getCategory() << endl;
	cout << "Date: " << News_To_Display[display].getDate() << endl;
	cout << "Published by: " << News_To_Display[display].getAdminFirstName() << " " << News_To_Display[display].getAdminSecondName() << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------\n";
	string choice;
	while (true) {
		cout << "\n1 -> Back to News Menu\n2 -> Back to search Menu\n3 -> Back to Main Menu\n\nEnter your choice: ";
		cin >> choice;
		if (choice == "1") {
			searchByDate();
			break;
		}
		else if (choice == "2")
		{
			goto flag_display;
			break;
		}
		else if (choice == "3") {
			Menus::readerMenu(*this);
			break;
		}
		else {
			cout << "Invalid Choice. Please try again.\n";
		}
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	Menus::readerMenu(*this);
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
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	string titleToView;
	cout << "\nEnter the title of the article you want to display: ";
	cin.ignore();
	getline(cin, titleToView);
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	for (auto news_To_View : News::News_Container)
	{

		if (news_To_View.first == titleToView)
		{
			// Display current details of the article
			cout << "------------------------------------------------------------------------------------------------";
			cout << "\nNews Title: " << news_To_View.first << endl;
			cout << "News Description: " << news_To_View.second.getDescription() << endl;
			cout << "News Category: " << news_To_View.second.getCategory() << endl;
			cout << "News Date: " << news_To_View.second.getDate() << endl;
			cout << "Average Rate: " << news_To_View.second.getRate() << endl;
		}
	}
	flag:
	cout << "\nEnter zero when you want to back ro your menu: ";
	string choose;
	cin >> choose;
	if (choose == "0")
		Menus::readerMenu(*this);
	else
	{
		cout << "Invalide Input .... Please try again";
		goto flag;
	}
}
