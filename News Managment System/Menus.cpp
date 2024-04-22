# include<iostream>
# include<string>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include"User.h"
#include"Admin.h"
#include"Reader.h"
#include "Menus.h"
#include "io_files.h"

void Menus::mainMenu(User user)
{
	string choice;
	system("cls");
flag:
	cout << "\n\n########################################################  Welcome To 7asebat News Managment System  ########################################################\n\n";
	cout << "\n1 -> Register" << endl;
	cout << "2 -> Login" << endl;
	cout << "3 -> Exit\n";
	cout << "\nEnter your choice: ";
	cin >> choice;

	if (choice == "1")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		system("cls");
		//Register function

		cout << "\t\t\t\t\t\t\t===================================" << endl;
		cout << "\t\t\t\t\t\t\t              REGISTER             " << endl;
		cout << "\t\t\t\t\t\t\t===================================" << endl;
		user.user_register();
		system("cls");
		goto flag;
	}

	else if (choice == "2")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		system("cls");
		//login function

		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "\t\t\t\t\t\t               LOGIN               " << endl;
		cout << "\t\t\t\t\t\t===================================" << endl;

		user.login(user);
		Menus::mainMenu(user);
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	}

	else if (choice == "3")
	{
		// Exit function
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		system("cls");
		Menus::Exit();

	}

	else {
		cout << "\nYour choice is wrong , please try again\n";
		goto flag;
	}
}

void Menus::Exit()
{
	cout << "\n\n####################################################  Thank you for using 7asebat News Managment System  ###################################################\n\n";
	io_files::save_reader_data();
	io_files::save_admin_data();
	io_files::save_news_data();
	system("pause");
	exit(0);
}

void Menus::adminMenu(Admin admin)
{
	string choice;
	while (true) {
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		system("cls");
		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "\t\t\t\t\t\t             Admin's Menu          " << endl;
		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "1. View News Articles\n";
		cout << "2. Add News\n";
		cout << "3. Update News\n";
		cout << "4. Delete News\n";
		cout << "5. Add Categories\n";
		cout << "6. Rate a Title\n";
		cout << "7. view Profile\n";
		cout << "8. Edit Profile\n";
		cout << "9. Log Out\n";
		cout << "10. Exit\n";
	flag:

		cout << "\nEnter your choice: ";
		cin >> choice;
		if (choice == "1")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.viewNewsArticles();
			cout << "Press 1 when want to Back to Admin Menu\n";
		}
		else if (choice == "2")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			admin.addNews();
		}
		else if (choice == "3")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			admin.editNews();
		}
		else if (choice == "4")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			admin.removeNews();
		}
		else if (choice == "5")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			admin.addCategories();
		}
		else if (choice == "6")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			admin.rateTitle();
		}
		else if (choice == "7")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			admin.view_proile();
		}
		else if (choice == "8")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			admin.editProfile(); 
		}
		else if (choice == "9")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			Menus::mainMenu(admin);
		}
		else if (choice == "10")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			Menus::Exit();
		}
		else
		{
			cout << "Invalid choice. Please enter a number between 1 and 7.\n";
			goto flag;
		}
	}
}

void Menus::readerMenu(Reader reader)
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	cout << "\t\t\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t\t\t            Reader Menu            " << endl;
	cout << "\t\t\t\t\t\t\t\t===================================" << endl;
	cout << "1. Latest News" << endl;
	cout << "2. Search by Category" << endl;
	cout << "3. Search by Keyword" << endl;
	cout << "4. Search by Title" << endl;
	cout << "5. Bookmarked News" << endl;
	cout << "6. Trending News" << endl;
	cout << "7. view Profile" << endl;
	cout << "8. Edit Profile" << endl;
	cout << "9. Log Out" << endl;
	cout << "10. Exit" << endl;
	cout << "\nEnter your choice: ";
flag01:
	string choice;
	cin >> choice;
	if (choice == "1")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.viewLatestNews();
	}
	else if (choice == "2")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.categorySearch();
	}
	else if (choice == "3")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.keywordSearch();
	}
	else if (choice == "4")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.titelSearch();
	}
	else if (choice == "5")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.bookmarkNews();
	}
	else if (choice == "6")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.trendingNews();
	}
	else if (choice == "7")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.view_proile();
	}
	else if (choice == "8")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.edit_profile();
	}
	else if (choice == "9")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		Menus::mainMenu(reader);
	}
	else if (choice == "10")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		Menus::Exit();
	}
	else
	{
		cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
		goto flag01;
	}
}

string Menus::getCurrentDate()
{
	auto now = chrono::system_clock::now();
	time_t currentTime;
	time(&currentTime);
	tm localTime;
	localtime_s(&localTime, &currentTime);
	ostringstream oss;
	oss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}