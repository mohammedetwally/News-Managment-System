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

// # Global Declarations


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
		cout << "incorrect fisrt name \n 1-to try again \n2-return to main Menus\n";
		int check;
		cin >> check;
		if (check == 1)
		{
			cout << "enter your first name \n";
			string f_name;
			cin.ignore();
			getline(cin, f_name);
			enter_first_name(f_name, user);
		}
		else
		{
			Menus::mainMenu(user);
			return;
		}
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
		cout << "incorrect second name \n 1-to try again \n2-return to main Menus\n";
		int check;
		cin >> check;
		if (check == 1)
		{
			cout << "enter your second name \n";
			cin.ignore();
			string s_name;
			getline(cin, s_name);
			enter_second_name(s_name, user);
		}
		else
		{
			Menus::mainMenu(user);
			return;
		}
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
		cout << "incorrect password  \n 1-to try again \n2-return to main Menus\n";
		int check;
		cin >> check;
		if (check == 1)
		{
			cout << "enter your password  \n";
			string pass;
			cin.ignore();
			getline(cin, pass);
			enter_password(pass, user);
		}
		else
		{
			Menus::mainMenu(user);
			return;
		}
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
	flag2:
		cout << "incorrect username  \n 1-to try again \n2-return to main Menus\n";
		int check;
		cin >> check;
		if (check == 1)
		{
			cout << "enter your username  \n";
			string user_name;
			cin.ignore();
			getline(cin, user_name);
			enter_username(user_name, user);
		}
		else if (check == 2)
		{
			Menus::mainMenu(user);
			return;
		}
		else {
			cout << "\nInvalid Choice\n";
			goto flag2;
		}
	}
}

User User::user_register()
{
	int strength;
	string confirmation_pass;
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
	getline(cin, password);
	enter_password(password, *this);

	// Password Confirmation

	cout << "\nConfirm your password: ";
	getline(cin, confirmation_pass);
	if (password == confirmation_pass)
	{

		// Check Password Strength 

		int check;
		strength = Test::password_strength(password);
		if (strength < 8)
		{
	flag9:
			cout << "\nWeak Password !!\n\n1 -> Enter a secure password\n2 -> continue";
			cin >> check;
			if (check == 1)
				goto flag;
			else if (check == 2)
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
			cout << "\nModerate Password !!\n\n1 -> Enter a secure password\n2 -> continue";
			cin >> check;
			if (check == 1)
				goto flag;
			else if(check == 2)
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
	Menus::mainMenu(*this);
	return *this;
	}
	else
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
		cout << "\nPassword is not matching\n";
		goto flag;
	}



}

void User::login(User user)
{
	int check;
	// takes username
	cout << "\nUsername: ";
	string username;
	cin.ignore();
	getline(cin, username);

	//takes password
	cout << "\nPassword: ";
	string password;
	getline(cin, password);

	// Check if exsit or not
	if (Test::existOrNot(user, password, username))
	{
		// if exsit
		///////////////////////////////
		// Check is it reader or admin
		if (user.getRole() == "reader")
		{
			// READER
			Reader reader = user;
			// check reader's data
			if (Test::readerValidation(reader, password, username))
			{
				Menus::readerMenu(reader);
			}
			else
			{
				cout << "Invalid Username or Password";
				cout << "\n1 -> Try again\n2 -> Back to main Menus";
				cin >> check;
				if (check == 1)
					login(reader);
				else if (check == 2)
					Menus::mainMenu(user);
			}
		}
		else if (user.getRole() == "admin")
		{
			// ADMIN
			Admin admin = user;
			// check admin's data
			if (Test::adminValidation(admin, password, username))
			{
				Menus::adminMenu(admin);
			}
			else
			{
				cout << "Invalid Username or Password";
				cout << "\n1 -> Try again\n2 -> Back to main Menus";
				cin >> check;
				if (check == 1)
					login(admin);
				else if (check == 2)
					Menus::mainMenu(user);
			}
		}
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
	}
	// if not
	else
	{
		int choose;
	flag:
		cout << "\nThis account is not exsit\n";
		cout << "1 -> Register\n";
		cout << "2 -> Back To Main Menus\n";
		cout << "3 -> Exit\n";
		cin >> choose;
		if (choose == 1)
			user.user_register();
		else if (choose == 2)
			Menus::mainMenu(user);
		else if (choose == 3)
			Menus::Exit();
		else
		{
			cout << "Invalid Choice ..... Please Try Again";
			goto flag;
		}
	}
}