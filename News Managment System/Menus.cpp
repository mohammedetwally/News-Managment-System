# include<iostream>
# include<string>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
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
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
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
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		system("cls");
		//login function

		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "\t\t\t\t\t\t               LOGIN               " << endl;
		cout << "\t\t\t\t\t\t===================================" << endl;

		user.login(user);
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));

	}

	else if (choice == "3")
	{
		// Exit function
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
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
	system("pause");
	exit(0);
}

void Menus::adminMenu(Admin admin)
{
	string choice;
	while (true) {
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
		system("cls");
		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "\t\t\t\t\t\t             Admin's Menu          " << endl;
		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "1. View News Articles\n";
		cout << "2. Manage Categories\n";
		cout << "3. Manage Users\n";
		cout << "4. Analytics and Reports\n";
		cout << "5. Edit News\n";
		cout << "6. view Profile\n";
		cout << "7. Edit Profile\n";
		cout << "8. Log Out\n";
		cout << "9. Exit\n";
	flag:

		cout << "\nEnter your choice: ";
		cin >> choice;
		if (choice == "1")
			admin.viewNewsArticles();
		else if (choice == "2")
			admin.manageCategories();
		else if (choice == "3")
			admin.manageUsers();
		else if (choice == "4")
			admin.analyticsAndReports();
		else if (choice == "5")
			admin.editNews();
		else if (choice == "6")
			admin.view_proile();
		else if (choice == "7")
			admin.editProfile();
		else if (choice == "8")
			Menus::mainMenu(admin);
		else if (choice == "9")
			Menus::Exit();
		else
		{
			cout << "Invalid choice. Please enter a number between 1 and 7.\n";
			goto flag;
		}
	}
}

void Menus::readerMenu(Reader reader)
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
	system("cls");
	cout << "\t\t\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t\t\t            Reader Menu            " << endl;
	cout << "\t\t\t\t\t\t\t\t===================================" << endl;
	cout << "1. Latest News" << endl;
	cout << "2. Search by Category" << endl;
	cout << "3. Search by Keyword" << endl;
	cout << "4. view Profile" << endl;
	cout << "5. Edit Profile" << endl;
	cout << "6. Log Out" << endl;
	cout << "7. Exit" << endl;
	cout << "\nEnter your choice: ";
flag01:
	string choice;
	cin >> choice;
	if (choice == "1")
	{
		// Latest News 
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.viewLatestNews();
	}
	else if (choice == "2")
	{
		// Latest News 
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.categorySearch();
	}
	else if (choice == "3")
	{
		// Latest News 
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.keywordSearch();
	}
	else if (choice == "4")
	{
		// Latest News 
		//this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.view_proile();
	}
	else if (choice == "5")
	{
		// Latest News 
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.edit_profile();
	}
	else if (choice == "6")
	{
		// Latest News 
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		Menus::mainMenu(reader);
	}
	else if (choice == "7")
	{
		// Latest News 
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		Menus::Exit();
	}
	else
	{
		cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
		goto flag01;
	}
}

