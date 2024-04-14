#include "Test.h"
#include"Menus.h"
# include"User.h"
bool Test::names_test(string name)
{
	if (name.empty())
		return false;
	for (int i = 0; i < name.length(); i++)
	{
		if (isalpha(name[i]))
			continue;
		else return false;
	}
	return true;
}

bool Test::space_test(string& word)
{
	if (word.empty())
		return false;
	for (int i = 0; i < word.length(); i++)
	{
		if (isspace(word[i]))
			return false;

	}
	return true;
}

int Test::password_strength(string password)
{
	int character = 0, sympol = 0, digit = 0;
	for (int i = 0; i < password.length(); i++)
	{
		if (password[i] >= '1' && password[i] <= '9')
			digit++;
		if (password[i] >= 'a' && password[i] <= 'z' || password[i] >= 'A' && password[i] <= 'Z')
			character++;
		if (password[i] >= 33 && password[i] <= 47 || password[i] >= 58 && password[i] <= 64 || password[i] >= 91 && password[i] <= 96 || password[i] >= 123 && password[i] <= 126)
			sympol++;
	}
	return (sympol + character + digit);
}

bool Test::adminValidation(Admin admin, string login_password, string login_username)
{
	if (admin.getUserName() == login_username)
	{
		if (admin.getPassword() == login_password)
		{
			return true;
		}
		return false;
	}
	else return false;
}

bool Test::readerValidation(Reader reader, string login_password, string login_username)
{
	if ((reader.getUserName()) == login_username)
	{
		if ((reader.getPassword()) == login_password)
		{
			return true;
		}
		return false;
	}
	else return false;
}

bool Test::user_check(User& user)
{
	return (user.getFirstName().size() && user.getSecondName().size()
		&& user.getUserName().size() && user.getPassword().size());
}

User Test::adminOrReader(User user)
{
	cout << "\n1 -> Register as an Admin ";
	cout << "\n2 -> Register as an Reader \n";
	int decision;
	cin >> decision;
	if (decision == 1)
	{
		Admin admin = user;
		admin.setRole("admin");
		//User::admin_container.insert(make_pair(make_pair(admin.getUserName(), admin.getPassword()), admin));
		return(admin);
	}
	else if (decision == 2)
	{
		Reader reader = user;
		reader.setRole("reader");
		//User::reader_container.insert(make_pair(make_pair(reader.getUserName(), user.getPassword()),reader));
		return reader;
	}
	else
	{
	flag:
		int choose;
		cout << "Invalid Choice";
		cout << "1 -> Try Again";
		cout << "2 -> Back to Main Menu";
		cin >> choose;
		if (choose == 1)
			adminOrReader(user);
		else if (choose == 2)
			Menus::mainMenu(user);
		else
		{
			cout << "Invalid Choice";
			goto flag;
		}
	}
}