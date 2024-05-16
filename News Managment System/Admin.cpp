#include <windows.h>
#include <thread>
#include <conio.h> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Admin.h"
#include <unordered_map>
#include "Test.h"
#include "Menus.h"
#include "News.h"

using namespace std;
unordered_map<string, News> News::News_Container;
map<string, User> Admin::admin_container;
set<string> Admin::categories;

// For editing admin's existing data
void Admin::editProfile()
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
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
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));
		cout << "\nPassword is not matching !!\n";
		goto flag;
	}
	// Edit FirstName
	string firstName;
	cout << "Enter new First Name: ";
	//cin.ignore();
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
	admin_container[this->getUserName()] = *this;
	Menus::adminMenu(*this);
}

void Admin::viewProfile()
{

	// Display current profile information
	cout << "\t\t\t\t\t\tyour data\n";
	cout << "\nUser Name: " << this->user_name << endl;
	cout << "Password: " << this->password << endl;
	cout << "First Name: " << this->first_name << endl;
	cout << "Second Name: " << this->second_name << endl;
	for (auto admin : News::News_Container)
	{
		if (this->getUserName() == admin.second.getAdminUserName())
		{
			cout << "Title: " << admin.second.getTitle();
			cout << "\nPublished by: " << admin.second.getAdminFirstName() << " " << admin.second.getAdminSecondName();
			cout << "\nCategory: " << admin.second.getCategory();
			cout << "\nDate: " << admin.second.getDate();
			cout << "\nRating: " << admin.second.getRate();
			cout << "\nDescription: " << admin.second.getDescription();
		}
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	Menus::adminMenu(*this);
}

// News management
void Admin::addNews()
{
	// Adds The Lastest News
	News news;
	string title;
	string description;
	string category;
	system("cls");
	cout << "\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t              Add News             " << endl;
	cout << "\t\t\t\t\t\t===================================\n\n" << endl;
	cout << "Please Enter News Data:\n\n";

	// Title Entery
flag:
	cout << "News Title: ";
	cin.ignore();
	getline(cin, title);
	if (Test::title_description_Test(title))
		news.setTitle(title);
	else
	{
		cout << "\nInvalid Title .... Please Try Again\n";
		goto flag;
	}

	// Description Entery
flag01:
	cout << "News Description: ";
	getline(cin, description);
	if (Test::title_description_Test(description))
		news.setDescription(description);
	else
	{
		cout << "\nInvalid Description .... Please Try Again\n";
		goto flag01;
	}

	// Category Entery
flag02:
	cout << "News Category: ";
	getline(cin, category);
	if (Test::category_test(category))
		news.setCategory(category);
	else
	{
		cout << "\nInvalid Category .... Please Try Again\n";
		goto flag02;
	}

	// check if exsist or not
	if (News::News_Container.find(title) != News::News_Container.end())
	{
		cout << "\n\nThis news is already exsist !!";
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
		Menus::adminMenu(*this);
	}

	// Set Date With Real Time

	news.setDate(Menus::getCurrentDate());
	cout << "Adding date: " << news.getDate() << endl;


	// Set Admin UserName
	news.setAdminUserName(user_name);
	news.setAdminFirstName(this->getFirstName());
	news.setAdminSecondName(this->getSecondName());

	cout << "\n\nNews Data: \n\n";
	cout << "Admin's UserName: " << news.getAdminUserName();
	cout << "\nAdmin's Name: " << news.getAdminFirstName() + " " + news.getAdminSecondName();
	cout << "\nNews Title: " << news.getTitle();
	cout << "\nNews Description: " << news.getDescription();
	cout << "\nNews Category: " << news.getCategory();
	cout << "\nNews Date: " << news.getDate() << endl;

	// Push in Hash Table
	News::News_Container.insert({ title, news });
flag03:
	cout << "\n\n1 -> Back to Admin Menu\n2 -> Add Another News\n";
	string choose;
	cin >> choose;
	if (choose == "1")
		Menus::adminMenu(*this);
	else if (choose == "2")
		this->addNews();
	else
	{
		cout << "\nInvalid Choose .... Please Try Again\n";
		goto flag03;
	}
}

void Admin::editNews() {

	// Display articles to select

	system("cls");
	cout << "\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t          Edit News             " << endl;
	cout << "\t\t\t\t\t\t===================================\n\n" << endl;


	// Ask for the title of the article to edit
	int titleToEdit;
	cout << "\nEnter the number of the article you want to update: ";
	int i = 0;
	for (auto news_To_Update : News::News_Container)
	{
		cout << "\n" << i + 1 << ": " << news_To_Update.second.getTitle();
		i++;
	}
	cin.ignore();
	cin >> titleToEdit;
	bool check;
	if (titleToEdit > News::News_Container.size())
	{
		check = true;
	}
	else
	{
		check = false;
	}
	titleToEdit -= 1;

	// Search for the article by title
	if (!check) {


		//check = false;

		// Display current details of the article
		unordered_map<string, News>::iterator it;
		it = News::News_Container.begin();
		it = next(it, titleToEdit);
		News* new_to_edit = &(it->second);
		new_to_edit->getCategory();

		cout << "News Title: " << new_to_edit->getTitle() << endl;
		cout << "News Description: " << new_to_edit->getDescription() << endl;
		cout << "News Category: " << new_to_edit->getCategory() << endl;
		cout << "News Date: " << new_to_edit->getDate() << endl;

		// Prompt for new details
		string newTitle, newDescription, newCategory;
		cout << "\nEnter new details (press Enter to keep the current value):\n";

		cout << "New Title: ";
		getline(cin, newTitle);
		if (!newTitle.empty()) {
			new_to_edit->setTitle(newTitle);
		}

		cout << "New Description: ";
		getline(cin, newDescription);
		if (!newDescription.empty()) {
			new_to_edit->setTitle(newDescription);
		}

		cout << "New Category: ";
		getline(cin, newCategory);
		if (!newCategory.empty()) {
			new_to_edit->setTitle(newCategory);
		}

		// Update the date
		new_to_edit->setDate(Menus::getCurrentDate());

		// Display updated details
		cout << "\nUpdated Details of the Article:\n";
		cout << "News Title: " << new_to_edit->getTitle() << endl;
		cout << "News Description: " << new_to_edit->getDescription() << endl;
		cout << "News Category: " << new_to_edit->getCategory() << endl;
		cout << "News Date: " << new_to_edit->getDate() << endl;

		cout << "\nNews article \"" << titleToEdit << "\" has been updated successfully.\n";
	}



	if (check)
		cout << "\narticle with the number \"" << titleToEdit << "\" not found.\n";

	Menus::adminMenu(*this);
}

void Admin::removeNews()
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	if (News::News_Container.empty())
	{
		cout << "\nThere is No News to delete\n";
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		Menus::adminMenu(*this);
	}
	else
	{
		// Display numbered list of news titles
		cout << "List of News:\n";
		int i = 1;
		for (auto& pair : News::News_Container) {
			cout << i << ". " << pair.second.getTitle() << endl;
			i++;
		}

		// Prompt user to choose a news by number
		size_t newsNumber = 0;
		while (true)
		{
		flag:
			cout << "Enter the number of the news you want to remove: ";
			cin >> newsNumber;
			// If input is out of range, handle error
			if (newsNumber < 1 || newsNumber > News::News_Container.size()) {
				cout << "Invalid news number. Please enter a valid number.\n";
				goto flag;
			}

			// Input is valid, break out of the loop
			else {
				break;
			}
		}

		// Find the news corresponding to the selected number
		auto it = News::News_Container.begin();
		advance(it, newsNumber - 1);

		// Remove the news from the container
		News::News_Container.erase(it);
		cout << "News removed successfully.\n";
	}
}

void Admin::viewNewsArticles()
{
	if (News::News_Container.size() == 0)
	{
		cout << "\nThere is no news articles\n\n";
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		Menus::adminMenu(*this);
	}
	int i = 1;
	for (auto display : News::News_Container) {
		cout << display.second.getAdminFirstName() + " " + display.second.getAdminSecondName() << endl;
		cout << i << "\n\nTitle : " << display.second.getTitle() << endl;
		cout << display.second.getDescription() << endl;
		cout << endl << display.second.getCategory() << endl;
		cout << "                                                         Date : " << display.second.getDate() << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------\n";
		i++;
	}
}

void Admin::rateTitle()
{
	system("cls");
	cout << "\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t             New's Rating          " << endl;
	cout << "\t\t\t\t\t\t===================================\n\n" << endl;


	string titleToEdit;
	cout << "\nEnter the title of the article you want to display its rate: ";
	cin.ignore();
	getline(cin, titleToEdit);

	for (auto news_To_Rate : News::News_Container)
	{

		if (news_To_Rate.first == titleToEdit)
		{
			// Display current details of the article

			cout << "News Title: " << news_To_Rate.first << endl;
			cout << "News Description: " << news_To_Rate.second.getDescription() << endl;
			cout << "News Category: " << news_To_Rate.second.getCategory() << endl;
			cout << "News Date: " << news_To_Rate.second.getDate() << endl;
			news_To_Rate.second.calcRate();
			cout << "Average Rate: " << news_To_Rate.second.getRate() << endl;
		}
	}
}

// Categories management
void Admin::addCategory() {

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	cout << "\t\t\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t\t\t            Add Category           " << endl;
	cout << "\t\t\t\t\t\t===================================\n\n" << endl;
flag11:
	string newCategory;
	cout << "\nEnter the name of the new category you want to add: ";
	cin.ignore();
	getline(cin, newCategory);
	for (int i = 0; i < newCategory.size(); i++)
	{
		if (isalpha(newCategory[i]))
			break;
		else
		{
			cout << "Invalid category .... Please try again";
			goto flag11;
		}
	}
	if (Admin::categories.count(newCategory) == 1)
	{
		cout << "\nERROR: Category already exists!";
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		system("cls");
	}
	else
	{
		cout << endl << newCategory << " added successfully\n\n";
		Admin::categories.insert(newCategory);
		cout << "The exsisting categories are: \n";
		for (auto a : categories)
		{
			int i = 1;
			cout << i << ". " << a << "\n";
			i++;
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));

		}
	}
}

void Admin::delete_category()
{
flag2019:
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
	system("cls");
	cout << "\nTAKE CARE !! Deleting any category will cause to delete the news which belongs to this category\n";
	cout << "1 -> Continue\n2 -> Back to your menu";
	cout << "\nEnter your choice: ";
	string check;
	cin >> check;
	if (check == "2")
	{
		Menus::adminMenu(*this);
	}
	else if (check != "1" && check != "2")
	{
		cout << "Invali choice .... Please try again";
		goto flag2019;
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
	if (Admin::categories.empty())
	{
		cout << "\nThere is no categories to delete\n";
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));

		Menus::adminMenu(*this);
	}
	else
	{
		int i = 1;
		cout << "---------------------------------------------------------------------------------------------------------";
		cout << "\nThe exsisting categories are: \n";
		for (auto a : categories)
		{
			cout << i << ". " << a << "\n";
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
			i++;
		}
		int categoryNumber = 0;
		while (true)
		{
		flag:
			cout << "Enter the number of the Category you want to remove: ";
			cin >> categoryNumber;
			// If input is out of range, handle error
			if (categoryNumber < 1 || categoryNumber > Admin::categories.size()) {
				cout << "Invalid category number. Please enter a valid number.\n";
				goto flag;
			}

			// Input is valid, break out of the loop
			else {
				break;
			}
		}
		// Find the category corresponding to the selected number
		auto it = Admin::categories.begin();
		advance(it, categoryNumber - 1);
		string selected_category = *it;



		//////////////////////////////////////////////////////////////////////////////////////////////////
		// Delete all News From this category
		int numDeleted = 0;
		for (auto it = News::News_Container.begin(); it != News::News_Container.end();)
		{
			if (it->second.getCategory() == selected_category) // assume category is a member of the news item
			{
				it = News::News_Container.erase(it);
				numDeleted++;
			}
			else
			{
				++it;
			}
		}


		// Remove the category from the container
		Admin::categories.erase(it);
		cout << "Category removed successfully.\n";
		cout << endl << numDeleted << " news items in the category have been deleted.\n";
		cout << "\nThe exsisting categories are: \n";
		int j = 1;
		for (auto a : categories)
		{
			cout << j << ". " << a << "\n";
			j++;
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
		}
	}
}