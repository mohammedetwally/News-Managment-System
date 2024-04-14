# include<iostream>
# include<string>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include "User.h"
#include "Test.h"
#include "Menus.h"
#include "Admin.h"
#include"Reader.h"
# include<map>



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

// Setters
void User::setUserName(string username)
{
	user_name = username;
}

void User::setPassword(string pass)
{
	password = pass;
}

void User::setFirstName(string first_name)
{
	this->first_name = first_name;
}

void User::setSecondName(string second_name)
{
	this->second_name = second_name;
}

void User::setRole(string role)
{
	this->role = role;
}



// taking data from user

   // First Name
void User::enter_first_name(string first_name, User& user)
{
	if (Test::names_test(first_name))
	{
		user.setFirstName(first_name);
	}
	else
	{
		cout << "incorrect fisrt name ..... Please Try Again\n\n";
		string f_name;
		getline(cin, f_name);
		enter_first_name(f_name, user);
	}
}

// Second Name
void User::enter_second_name(string second_name, User& user)
{
	if (Test::names_test(second_name))
	{
		user.setSecondName(second_name);
	}
	else
	{
		cout << "incorrect second name ..... Please Try Again\n\n";
		string s_name;
		getline(cin, s_name);
		enter_second_name(s_name, user);
	}
}

// Password
void User::enter_password(string password, User& user)
{
	if (Test::space_test(password))
	{
		user.setPassword(password);
	}
	else
	{
		cout << "incorrect password ..... Please Try Again \n\n";
		string pass;
		getline(cin, pass);
		enter_password(pass, user);
	}
}

// Username
void User::enter_username(string username, User& user)
{
	if (Test::space_test(username))
	{
		user.setUserName(username);
	}
	else
	{
		cout << "incorrect username ..... Please Try Again";
		string user_name;
		getline(cin, user_name);
		enter_username(user_name, user);
	}
}

void User::user_register()
{
	int strength;
	// First Name Entry
flag1:
	cout << "\nEnter your first name: ";
	string first_name;
	cin.ignore();
	getline(cin, first_name);
	enter_first_name(first_name, *this);
	if (!Test::names_test)
	{
		cout << "Invalid Name ..... Please Try Again";
		goto flag1;
	}

	// Second Name Entry
flag2:
	cout << "\nEnter your second name: ";
	string second_name;
	getline(cin, second_name);
	enter_second_name(second_name, *this);
	if (!Test::names_test)
	{
		cout << "Invalid Name ..... Please Try Again";
		goto flag2;
	}

	// Username Entry
flag3:
	cout << "\nEnter your username: ";
	string username;
	getline(cin, username);
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
	enter_username(username, *this);
	if (!Test::user_check)
	{
		cout << "Invalid Name ..... Please Try Again";
		goto flag3;
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
				cout << "\n1 -> Try again\n2 -> Back to main Menus";
				cout << "\nEnter your choice: ";
				cin >> check;
				if (check == "1")
					login(reader_it->second);
				else if (check == "2")
					Menus::mainMenu(user);
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
				cout << "Invalid Username or Password";
				cout << "\n1 -> Try again\n2 -> Back to main Menus";
				cout << "\nEnter your choice: ";
				cin >> check;
				if (check == "1")
					login(admin_it->second);
				else if (check == "2")
					Menus::mainMenu(user);
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
				Menus::mainMenu(user);
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
			user.user_register();
		else if (choose == "2")
			Menus::mainMenu(user);
		else if (choose == "3")
			Menus::Exit();
		else
		{
			cout << "Invalid Choice ..... Please Try Again";
			goto flag;
		}
	}
}