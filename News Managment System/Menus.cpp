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

void Menus::mainMenu(User user)
{
	string choice;
	system("cls");
	cout << "\n\n#######################################################  Welcome To 7asebat News Managment System  #######################################################\n\n";
flag:
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
		user = user.user_register();
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		system("cls");
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
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
	cout << "\n\n####################################################  Thank you for using 7asebat News Managment System  ###################################################\n\n";
	chrono::seconds dura(3);
	system("pause");
	exit(0);
}

void Menus::adminMenu(Admin admin)
{
	int choice;
	while (true) {
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
		system("cls");
		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "\t\t\t\t\t             Admin's Menu          " << endl;
		cout << "\t\t\t\t\t\t===================================" << endl;
		cout << "1. View News Articles\n";
		cout << "2. Manage Categories\n";
		cout << "3. Manage Users\n";
		cout << "4. Analytics and Reports\n";
		cout << "5. Edit News\n";
		cout << "6. Edit Profile\n";
		cout << "7. Log Out\n";
		cout << "8. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			admin.viewNewsArticles();
			break;
		case 2:
			admin.manageCategories();
			break;
		case 3:
			admin.manageUsers();
			break;
		case 4:
			admin.analyticsAndReports();
			break;
		case 5:
			admin.editNews();
			break;
		case 6:
			admin.editProfile(admin);
			break;
		case 7:
			Menus::mainMenu(admin);
			break;
		case 8:
			Menus::Exit();
			return;
		default:
			cout << "Invalid choice. Please enter a number between 1 and 7.\n";
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
	cout << "4. Edit Profile" << endl;
	cout << "5. Log Out" << endl;
	cout << "6. Exit" << endl;
	cout << "\nEnter your choice: ";
	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		// Latest News 
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.viewLatestNews();
		break;
	case 2:
		// Search by category
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.categorySearch();
		break;
	case 3:
		// Search by Keyword
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.keywordSearch();
		break;
	case 4:
		// Edit Profile
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		reader.edit_profile(reader);
		break;
	case 5:
		// Back to main menu
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		Menus::mainMenu(reader);
		break;
	case 6:
		// Exit
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
		Menus::Exit();
		break;
	default:
		cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
	}
}

