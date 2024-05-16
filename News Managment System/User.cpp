#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include "User.h"
#include "Test.h"
#include "Menus.h"
#include "Admin.h"
#include "Reader.h"

// Getters
string User::getFirstName()
{
	return first_name;
}
string User::getSecondName()
{
	return second_name;
}

string User::getUserName()
{
	return user_name;
}
string User::getPassword()
{
	return password;
}
string User::getRole()
{
	return role;
}

string User::getLastLoginDate() {
	return lastLoginDate;
}

set<string> User::getPreferredCategories() {
	return preferredCategories;
}

// Setters
void User::setFirstName(string first_name)
{
	this->first_name = first_name;
}
void User::setSecondName(string second_name)
{
	this->second_name = second_name;
}

void User::setUserName(string username)
{
	user_name = username;
}
void User::setPassword(string pass)
{
	password = pass;
}
void User::setRole(string role)
{
	this->role = role;
}

void User::setLastLoginDate(string date) {
	lastLoginDate = date;
}
void User::setLastLoginDateAsCurrent() {
	lastLoginDate = Menus::getCurrentDate();
}

void User::setPreferredCategories(string preferredCategory) {
	preferredCategories.insert(preferredCategory);
}

// registeration functions
void User::enter_first_name(string first_name, User& user)
{
	if (Test::names_test(first_name))
	{
		user.setFirstName(first_name);
	}
	else
	{
		cout << "\nincorrect fisrt name ..... Please Try Again: ";
		string f_name;
		getline(cin, f_name);
		enter_first_name(f_name, user);
	}
}
void User::enter_second_name(string second_name, User& user)
{
	if (Test::names_test(second_name))
	{
		user.setSecondName(second_name);
	}
	else
	{
		cout << "\nincorrect fisrt name ..... Please Try Again: ";
		string s_name;
		getline(cin, s_name);
		enter_second_name(s_name, user);
	}
}
void User::enter_password(string password, User& user)
{
	if (Test::space_test(password))
	{
		user.setPassword(password);
	}
	else
	{
		cout << "\nincorrect fisrt name ..... Please Try Again: ";
		string pass;
		getline(cin, pass);
		enter_password(pass, user);
	}
}
void User::enter_username(string username, User& user)
{
	if (Test::space_test(username))
	{
		user.setUserName(username);
	}
	else
	{
		cout << "\nincorrect fisrt name ..... Please Try Again: ";
		string user_name;
		getline(cin, user_name);
		enter_username(user_name, user);
	}
}
void User::preferred_categories(User& user)
{
	int counter = 1;
	map<int, string>link;
	cout << "the categories allowed\n";
	for (auto category : Admin::categories)
	{
		cout << counter << " - " << category << endl;
		link[counter] = category;
		counter++;
	}
	if (Admin::categories.empty())
	{
		cout << "no categories\n";
	}
	int count = 0;
	for (int i = 1; i <= 3; i++)
	{
		cout << "\nChoose from the list of categories\n\n";
		int choice;
		cin >> choice;
		if (choice <= link.size())
		{
			if (preferredCategories.find(link[choice]) == preferredCategories.end())
			{
				preferredCategories.emplace(link[choice]);
				cout << "The category was added successfully\n";
			}
			else
			{
				cout << "you have choose it before .............please choose another one\n";
				i--;
			}
		}
		else if (choice > 3 || choice < 1)
		{
			cout << "invalid value please try again";
			i--;
		}
		count = i;
	}
	if (count == 3 && link.size() == 3)
	{
		cout << "your categoriese was added successfully\n";
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));

}

void User::user_register()
{
	int strength;
	// First Name Entry
	cout << "\nEnter your first name: ";
	string first_name;
	cin.ignore();
	getline(cin, first_name);
	enter_first_name(first_name, *this);

	// Second Name Entry
	cout << "\nEnter your second name: ";
	string second_name;
	getline(cin, second_name);
	enter_second_name(second_name, *this);
	// Username Entry
flag3:
	cout << "\nEnter your username: ";
	string username;
	getline(cin, username);
	enter_username(username, *this);
	for (auto check : Admin::admin_container)
	{
		if (check.second.getUserName() == username)
		{
			cout << "this username is exist please try again\n";
			goto flag3;
		}
	}
	for (auto check : Reader::reader_container)
	{
		if (check.second.getUserName() == username)
		{
			cout << "this username is exist please try again\n";
			goto flag3;
		}
	}

	// Password Entry
flag:
	cout << "\nEnter your password: ";
	string password;
	string confirmation_pass;
	getline(cin, password);
	enter_password(password, *this);

	// Password Confirmation

	cout << "\nConfirm your password: ";
	getline(cin, confirmation_pass);
	if (password == confirmation_pass)
	{

		// Check Password Strength 

		string check;
		strength = Test::password_strength(password);
		if (strength < 8)
		{
		flag9:
			cout << "\nWeak Password !!\n\n1 -> Enter a secure password\n2 -> continue\n";
			cout << "\nEnter your choice: ";
			cin >> check;
			if (check == "1")
			{
				cin.ignore();
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
				cin.ignore();
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

		// Reader or Admin Registeration
		*this = Test::adminOrReader(*this);
		if (this->getRole() == "reader")
		{
			pair<string, string>p;
			p.first = this->getUserName();
			p.second = this->getPassword();
			preferred_categories(*this);

			pair<string, User> keyValue = make_pair(this->getUserName(), *this);
			Reader::reader_container.insert(keyValue);


		}
		else if (this->getRole() == "admin")
		{
			pair<string, User> keyValue = make_pair(this->getUserName(), *this);
			Admin::admin_container.insert(keyValue);
		}
	}
	else
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
		cout << "\nPassword is not matching !!\n";
		goto flag;
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
	Menus::mainMenu();
}

void User::login(User user)
{

	string check;
	// takes username
	cout << "\nUsername: ";
	string username;
	cin.ignore();
	getline(cin, username);

	//takes password

	cout << "\nPassword: ";
	string password;
	getline(cin, password);


	auto reader_it = Reader::reader_container.find(username);
	auto admin_it = Admin::admin_container.find(username);
	Reader reader;
	Admin admin;

	// Check if exist or not
	if (reader_it != Reader::reader_container.end() || admin_it != Admin::admin_container.end())
	{
		if (reader_it != Reader::reader_container.end())
		{
			reader = reader_it->second;

			if (Test::readerValidation(reader, password, username))
			{
				cout << "\n\nHello " << reader_it->second.getFirstName() << " " << reader_it->second.getSecondName();
				Menus::readerMenu(reader_it->second);
			}
			else
			{
				cout << "Invalid Username or Password";
			flag2001:

				cout << "\n1 -> Try again\n2 -> Back to main Menus";
				cout << "\nEnter your choice: ";
				cin >> check;
				if (check == "1")
					login(reader_it->second);
				else if (check == "2")
					Menus::mainMenu();
				else
				{
					cout << "Invalid choice .... Please try again";
					goto flag2001;
				}
			}
		}
		else if (admin_it != Admin::admin_container.end())
		{
			admin = admin_it->second;
			if (Test::adminValidation(admin, password, username))
			{
				cout << "\n\nHello " << admin.getFirstName() << " " << admin.getSecondName();
				Menus::adminMenu(admin_it->second);
			}
			else
			{
			flag2002:
				cout << "\nInvalid Username or Password";
				cout << "\n1 -> Try again\n2 -> Back to main Menus";
				cout << "\nEnter your choice: ";
				cin >> check;
				if (check == "1")
					login(admin_it->second);
				else if (check == "2")
					Menus::mainMenu();
				else
				{
					cout << "Invalid choice .... Please try again";
					goto flag2002;
				}
			}
		}
		else
		{
		flag02:
			string decision;
			cout << "Invalid Account !!\n\n";
			cout << "1 -> Try Again\n";
			cout << "2 -> Back To Main Menu\n";
			cout << "3 -> Exit\n";
			cin >> decision;
			if (decision == "1")
				login(user);
			else if (decision == "2")
				Menus::mainMenu();
			else if (decision == "3")
				Menus::Exit();
			else
			{
				cout << "Invalide Choice !! ..... Please Try Again";
				goto flag02;
			}

		}

	}
	// if not
	else
	{
		string choose;
	flag:
		cout << "\nThis account doesn't exist\n";
		cout << "1 -> Register\n";
		cout << "2 -> Back To Main Menus\n";
		cout << "3 -> Exit\n";
		cout << "\nEnter your choice: ";
		cin >> choose;
		if (choose == "1")
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
			system("cls");
			user.user_register();
		}
		else if (choose == "2")
			Menus::mainMenu();
		else if (choose == "3")
			Menus::Exit();
		else
		{
			cout << "Invalid Choice ..... Please Try Again";
			goto flag;
		}
	}
}