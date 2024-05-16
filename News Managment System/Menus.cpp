#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "User.h"
#include "Admin.h"
#include "Reader.h"
#include "Menus.h"
#include "io_files.h"


void Menus::mainMenu()
{
	User user;
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
		//		Menus::mainMenu(user);
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
	io_files::save_categories();
	io_files::save_comments();

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
		cout << "6. Delete Categories\n";
		cout << "7. Rate a Title\n";
		cout << "8. view Profile\n";
		cout << "9. Edit Profile\n";
		cout << "10. Log Out\n";
		cout << "11. Exit\n";
	flag:

		cout << "\nEnter your choice: ";
		cin >> choice;
		if (choice == "1")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			string choose;
			admin.viewNewsArticles();
			cout << "Press 0 when want to Back to Admin Menu\n";
			cin >> choose;
			if (choose == "0")
				adminMenu(admin);
			else
				admin.viewNewsArticles();

		}
		else if (choice == "2")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.addNews();
		}
		else if (choice == "3")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.editNews();
		}
		else if (choice == "4")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.removeNews();
		}
		else if (choice == "5")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.addCategory();
		}
		else if (choice == "6")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.delete_category();
		}
		else if (choice == "7")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.rateTitle();
		}
		else if (choice == "8")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.viewProfile();
		}
		else if (choice == "9")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			admin.editProfile();
		}
		else if (choice == "10")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			Menus::mainMenu();
		}
		else if (choice == "11")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			Menus::Exit();
		}
		else
		{
			cout << "Invalid choice. Please enter a number between 1 and 11.\n";
			goto flag;
		}
	}
}

void Menus::readerMenu(Reader reader)
{
	for (int i = 0; i < reader.bookmarking_container.size(); i++) {
		reader.bookmarking_container[i]->bookmarkedOrNo = true;
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	cout << "\t\t\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t\t\t            Reader Menu            " << endl;
	cout << "\t\t\t\t\t\t\t\t===================================" << endl;
	cout << "1. Notifications List" << endl;
	cout << "2. Latest News" << endl;
	cout << "3. Search by Category" << endl;
	cout << "4. Search by Keyword" << endl;
	cout << "5. Search by Title" << endl;
	cout << "6. Search by Date" << endl;
	cout << "7. Bookmarked News" << endl;
	cout << "8. Trending News" << endl;
	cout << "9. Show Preferred News" << endl;
	cout << "10. View Profile" << endl;
	cout << "11. Edit Profile" << endl;
	cout << "12. Log Out" << endl;
	cout << "13. Exit" << endl;
	cout << "\nEnter your choice: ";
flag01:
	string choice;
	cin >> choice;
	if (choice == "1")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.notifications();
	}
	else if (choice == "2")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.viewLatestNews();
	}
	else if (choice == "3")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.categorySearch();
	}
	else if (choice == "4")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.keywordSearch();
	}
	else if (choice == "5")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.titleSearch();
	}
	else if (choice == "6")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.searchByDate();
		cin.ignore();
	}
	else if (choice == "7")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.viewBookmarkedNews();
	}
	else if (choice == "8")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.trendingNews();
	}
	else if (choice == "9")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.showPreferredNews();
	}
	else if (choice == "10")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.view_profile();
	}
	else if (choice == "11")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.edit_profile();
	}
	else if (choice == "12")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		Reader::reader_container[reader.getUserName()].setLastLoginDateAsCurrent();
		Menus::mainMenu();
	}
	else if (choice == "13")
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		reader.removeAllBookmarkedNewsFromNewsContainer();
		Reader::reader_container[reader.getUserName()].bookmarking_container = reader.bookmarking_container;
		Reader::reader_container[reader.getUserName()].setLastLoginDateAsCurrent();
		Menus::Exit();
	}
	else
	{
		cout << "Invalid choice. Please enter a number between 1 and 13." << endl;
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