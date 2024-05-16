#include "Test.h"
#include "Menus.h"
#include "User.h"

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
		else if (password[i] >= 'a' && password[i] <= 'z' || password[i] >= 'A' && password[i] <= 'Z')
			character++;
		else if (password[i] >= 33 && password[i] <= 47 || password[i] >= 58 && password[i] <= 64 || password[i] >= 91 && password[i] <= 96 || password[i] >= 123 && password[i] <= 126)
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

User Test::adminOrReader(User user)
{
	cout << "\n1 -> Register as an Admin ";
	cout << "\n2 -> Register as an Reader \n";
	cout << "\n\nEnter your choice: ";
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
			Menus::mainMenu();
		else
		{
			cout << "Invalid Choice";
			goto flag;
		}
	}
}

bool Test::user_check(User& user)
{
	return (user.getFirstName().size() && user.getSecondName().size()
		&& user.getUserName().size() && user.getPassword().size());
}

bool Test::title_description_Test(string title_description)
{
	if (title_description.empty())
		return false;
	else
	{
		int character = 0, sympol = 0, digit = 0;
		for (int i = 0; i < title_description.length(); i++)
		{
			if (title_description[i] >= '1' && title_description[i] <= '9')
				digit++;
			else if (title_description[i] >= 'a' && title_description[i] <= 'z' || title_description[i] >= 'A' && title_description[i] <= 'Z')
				character++;
			else if (title_description[i] >= 33 && title_description[i] <= 47 || title_description[i] >= 58 && title_description[i] <= 64 || title_description[i] >= 91 && title_description[i] <= 96 || title_description[i] >= 123 && title_description[i] <= 126)
				sympol++;
		}
		if (character == 0)
			return false;
		else
			return true;
	}
}

bool Test::category_test(string category)
{
	if (category.empty())
		return false;
	else
	{
		for (int i = 0; i < category.length(); i++)
		{
			if (isalpha(category[i]) || category[i] == ' ' || category[i] == '&')
				continue;
			else return false;
		}
		return true;
	}
}

bool Test::rate_test(string rate)
{
	if (rate >= "0" && rate <= "5")
	{
		for (int i = 0; i < rate.size(); i++)
		{
			if (isdigit(rate[i]))
			{
				if (rate[1] = 46)
					return true;
				return true;
			}
			else return false;
		}
	}
	else return false;
}

bool Test::compareByDate(pair<string, News> a, pair<string, News> b)
{
	return a.second.getDate() < b.second.getDate();
}

bool Test::isDate(string inputStr)
{
	istringstream ss(inputStr);
	tm date = {};
	ss >> get_time(&date, "%Y-%m-%d");
	return !ss.fail();
}

string Test::extractDate(string fullDate)
{
	istringstream ss(fullDate);
	string date;
	ss >> date;
	return date;
}

bool Test::testComment(string comment)
{

	if (comment.empty())
		return false;
	else
	{
		int character = 0, sympol = 0, digit = 0;
		for (int i = 0; i < comment.length(); i++)
		{
			if (comment[i] >= '1' && comment[i] <= '9')
				digit++;
			else if (comment[i] >= 'a' && comment[i] <= 'z' || comment[i] >= 'A' && comment[i] <= 'Z')
				character++;
			else if (comment[i] >= 33 && comment[i] <= 47 || comment[i] >= 58 && comment[i] <= 64 || comment[i] >= 91 && comment[i] <= 96 || comment[i] >= 123 && comment[i] <= 126)
				sympol++;
		}
		if (character == 0)
			return false;
		else
			return true;
	}
}