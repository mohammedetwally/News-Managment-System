#include <iostream>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include <algorithm>
#include "News.h"
#include "Reader.h"
#include "Test.h"
#include "Menus.h"
#include "Admin.h"

using namespace std;
map<string, Reader> Reader::reader_container;
map<News, stack<string>> Reader::commentsMap;


// Reader data
void Reader::edit_profile()
{
	//this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(3));
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
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
		cout << "\nPassword is not matching !!\n";
		goto flag;
	}
	// Edit FirstName
	string firstName;
	cout << "Enter new First Name: ";
	cin.ignore();
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
	reader_container[this->getUserName()] = *this;
	Menus::readerMenu(*this);

}

void Reader::view_profile()
{
	system("cls");

	cout << "\t===---=== PROFILE ===---===\n\n";
	cout << "Current User Name: " << this->user_name << endl;
	cout << "Current Password: " << this->password << endl;
	cout << "Current First Name: " << this->first_name << endl;
	cout << "Current Second Name: " << this->second_name << endl;
	cout << "Previous Login Date: " << this->lastLoginDate;
	cout << "your preferrd categories is : ";
	for (auto news : preferredCategories)
	{
		cout << news << "\t";
	}

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(5000));
	Menus::readerMenu(*this);
}


// Viewing news
bool Reader::displayNewsArticle(News news) {
	cin.ignore();
redo:
	system("cls");
	if (news.bookmarkedOrNo)
		cout << "\n" << "\033[1;33m" << "* " << "\033[0m";
	cout << "Title: " << news.getTitle();
	cout << "\nPublished by: " << news.getAdminFirstName() << " " << news.getAdminSecondName();
	cout << "\nCategory: " << news.getCategory();
	cout << "\nDate: " << news.getDate();
	cout << "\nRating: " << news.getRate();
	cout << "\nDescription: " << news.getDescription();
	cout << "\nNo. of mark as spam: " << news.getSpamSet().size();
	displayNewsWithComments(news);

	string selection;
	cout << "\n\n1. Comments\n2. Rate the article\n3. Bookmark\n4. Mark as spam";
	cout << "\n5. View another article\n6. Return to main menu\n\nSelection: ";

redoMenuSelection:
	getline(cin, selection);

	if (selection == "1")
	{
		comment(news);
		goto redo;
	}
	else if (selection == "2") {
		rateNews(news);
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
		goto redo;
	}
	else if (selection == "3") {
		bookmarkNews(&(News::News_Container[news.getTitle()]));
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
		goto redo;
	}
	else if (selection == "4") {
		News::News_Container[news.getTitle()].addSpamSet(this->getUserName());
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(1000));
		return true;
	}
	else if (selection == "5")
	{
		system("cls");
		return true;
	}
	else if (selection == "6")
	{
		return false;
	}
	else {
		cout << "\nERROR: Invalid selection!\nEnter a valid number: ";
		goto redoMenuSelection;
	}
}

void Reader::viewLatestNews()
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");

	map<string, News> orderedNews;
	set<string> preferredNews = this->getPreferredCategories();
	for (auto i = News::News_Container.begin(); i != News::News_Container.end(); i++) {
		orderedNews.insert(make_pair(i->second.getDate(), i->second));
	}

	cin.ignore();

redo:
	int i = 0;
	int news_to_view;
	for (auto news = orderedNews.rbegin(); news != orderedNews.rend(); news++)
	{
		if (news->second.bookmarkedOrNo)
			cout << "\n" << "\033[1;33m" << "* " << "\033[0m" << i + 1 << ": " << news->second.getTitle() << endl;
		else
			cout << "\n" << i + 1 << ": " << news->second.getTitle() << endl;

		i++;
	}

	cout << "\nEnter the number of the article you want to view: ";
	cin >> news_to_view;
	if (news_to_view > orderedNews.size() || news_to_view < 1)
	{
		cout << "Invalid Choice .... Please try again";
		viewLatestNews();
	}
	else
	{
		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));

		map<string, News>::reverse_iterator it = orderedNews.rbegin();
		advance(it, news_to_view - 1);
		if (displayNewsArticle(it->second))
			goto redo;
	}

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	Menus::readerMenu(*this);
}

void Reader::trendingNews()
{
	system("cls");
redo:
	int counter = 1;
	for (auto news : News::News_Container)
	{
		if (stoi(Test::extractDate(news.second.getDate()).substr(0, 4)) - stoi(Test::extractDate(Menus::getCurrentDate()).substr(0, 4)) == 0 &&
			stoi(Test::extractDate(news.second.getDate()).substr(5, 2)) - stoi(Test::extractDate(Menus::getCurrentDate()).substr(5, 2)) == 0 &&
			stoi(Test::extractDate(Menus::getCurrentDate()).substr(8, 2)) - stoi(Test::extractDate(news.second.getDate()).substr(8, 2)) <= 2 &&
			news.second.getRate() >= 3)
		{
			cout << counter << " - title : " << news.second.getTitle() << endl;
			counter++;
		}
	}
	cout << "enter the number of news you want to see\n";
flag:
	int choice;
	cin >> choice;
	if (choice<1 || choice>counter)
	{
		cout << "invalid value \n1-try again\n2-return to main menu\n";
	flag1:
		int choose;
		cin >> choose;
		if (choose < 1 || choose>2)
		{
			cout << "invalid value please try agian\n";
			goto flag1;
		}
		else if (choose == 1)
		{
			goto flag;
		}
		else
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
			Menus::readerMenu(*this);
		}
	}
	else
	{
		int iterate = 1;
		for (auto news : News::News_Container)
		{
			if (stoi(Test::extractDate(news.second.getDate()).substr(0, 4)) - stoi(Test::extractDate(Menus::getCurrentDate()).substr(0, 4)) == 0 &&
				stoi(Test::extractDate(news.second.getDate()).substr(5, 2)) - stoi(Test::extractDate(Menus::getCurrentDate()).substr(5, 2)) == 0 &&
				stoi(Test::extractDate(news.second.getDate()).substr(8, 2)) - stoi(Test::extractDate(Menus::getCurrentDate()).substr(8, 2)) <= 2)
			{
				if (iterate == choice)
				{
					/*cout << " - title : " << news.second.getTitle() << endl;
					cout << "discription : " << news.second.getDescription() << endl;
					cout << "rate : " << news.second.news_rate << endl;
					cout << "data : " << news.second.getDate() << endl;
					cout << "written by : " << news.second.getAdminUserName() << endl << endl;
					this->rateNews(news.second);*/
					if (displayNewsArticle(news.second))
						goto redo;
				}
				else iterate++;
			}
		}
	}

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
	Menus::readerMenu(*this);
}

void Reader::showPreferredNews()
{
redo:
	int counter = 1;
	for (auto it : News::News_Container)
	{
		if (preferredCategories.count(it.second.getCategory()))
		{
			if (it.second.bookmarkedOrNo)
				cout << "\033[1;33m" << "* " << "\033[0m";
			cout << counter << " - title : " << it.second.getTitle() << endl;
			cout << "discription : " << it.second.getDescription() << endl;
			cout << "rate : " << it.second.news_rate << endl;
			cout << "data : " << it.second.getDate() << endl;
			cout << "written by : " << it.second.getAdminUserName() << endl << endl;
			cout << "\t\t\t\t\t\========================================================\t\t\t\t\t\t\n";
			counter++;
		}
	}
	cout << "enter the number of news you want to see\n";
flag:
	int choice;
	cin >> choice;
	if (choice<1 || choice>counter)
	{
		cout << "invalid value \n1-try again\n2-return to main menu\n";
	flag1:
		int choose;
		cin >> choose;
		if (choose < 1 || choose>2)
		{
			cout << "invalid value please try agian\n";
			goto flag1;
		}
		else if (choose == 1)
		{
			goto flag;
		}
		else
		{
			this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
			Menus::readerMenu(*this);
		}
	}
	else
	{
		int iterate = 1;
		for (auto it : News::News_Container)
		{
			if (preferredCategories.count(it.second.getCategory()) && iterate == choice)
			{
				//	system("cls");
				//	cout << "title : " << it.second.getTitle() << endl;
				//	cout << "discription : " << it.second.getDescription() << endl;
				//	cout << "rate : " << it.second.news_rate << endl;
				//	cout << "data : " << it.second.getDate() << endl;
				//	cout << "written by : " << it.second.getAdminUserName() << endl << endl;
				//	cout << "\t\t\t\t\t\========================================================\t\t\t\t\t\t\n";
				//	string selection;
				//	cout << "\n\n1. Bookmark the article\n2. Mark the article as spam";
				//	cout << "\n3. Return to news menu\n4. Return to main menu\n\nSelection: ";
				//	cin.ignore();
				//redoMenuSelection:
				//	getline(cin, selection);
				//	if (selection == "1") {
				//		// call bookmark function
				//	}
				//	else if (selection == "2") {
				//		//News::News_Container[it.second.getTitle()].addSpamSet(this->getUserName());
				//	}
				//	else if (selection == "3")
				//		viewLatestNews();
				//	else if (selection == "4")
				//		Menus::readerMenu(*this);
				//	else {
				//		cout << "\nERROR: Invalid selection!\nEnter a valid number: ";
				//		goto redoMenuSelection;
				//	}
				if (displayNewsArticle(it.second))
					goto redo;
				break;
			}
			else if (preferredCategories.count(it.second.getCategory()) && iterate != choice)
				iterate++;
		}

	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
	Menus::readerMenu(*this);
}

void Reader::viewBookmarkedNews()
{
	system("cls");
	if (bookmarking_container.size() == 0) {
		cout << "No Bookmarked News Now !";
		return;
	}
	cout << "Bookmarked News\n";
	cout << "===============\n\n";
redo:
	int i = 1;
	for (auto news : bookmarking_container) {

		cout << endl << "\033[1;33m" << "* " << "\033[0m" << i << ". Title : " << news->getTitle() << endl;
		i++;
	}

	while (true) {
		cout << "\n\n1. View article\n2. Remove bookmark new \n3. Remove all\n4. return to main menu\n\n";
		int new_num;
		cin >> new_num;

		if (new_num == 1) {
			while (true) {
				cout << "\nEnter the number of the article you want to view: ";
				cin >> new_num;
				if (new_num >= 1 && new_num <= bookmarking_container.size()) break;
				else {
					cout << "Wrong choice , try again.\n";
				}
			}
			/*this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
			system("cls");
			News new_details = *bookmarking_container[new_num - 1];
			cout << "\n\n" << "\033[1;33m" << "* " << "\033[0m" << "Title : " << new_details.getTitle() << endl;
			cout << new_details.getDescription() << endl;
			cout << endl << new_details.getCategory();
			cout << "                                                         Date : " << new_details.getDate() << endl;
			cout << "This news Published by: " << new_details.getAdminFirstName() + " " + new_details.getAdminSecondName() << endl;
			cout << "-------------------------------------------------------------------------------------------------------------------------\n";
			displayNewsWithComments(new_details);
			comment(new_details);*/
			if (displayNewsArticle(*bookmarking_container[new_num - 1]))
				goto redo;
			break;
		}
		else if (new_num == 2) {
			while (true) {
				cout << "\nEnter the number of the article you want to remove the bookmark for it: ";
				cin >> new_num;
				if (new_num >= 1 && new_num <= bookmarking_container.size()) break;
				else {
					cout << "Wrong choice , try again.\n";
				}
			}
			vector<News*>::iterator it;
			it = bookmarking_container.begin();
			it = next(it, new_num - 1);
			(*it)->bookmarkedOrNo = false;
			bookmarking_container.erase(it);
			cout << "\nthe news bookmarked removed successfully";
			break;

		}
		else if (new_num == 3) {
			vector<News*>::iterator it = bookmarking_container.begin();
			for (; it != bookmarking_container.end(); it++) {
				(*it)->bookmarkedOrNo = false;
			}
			bookmarking_container.clear();
			cout << "\nALL bookmarked news removed successfully";
			break;
		}
		else if (new_num == 4) {
			Menus::readerMenu(*this);
		}
		else {
			cout << "Wrong choice , try again.\n";
		}

	}
	Menus::readerMenu(*this);
}

void Reader::notifications()
{
	system("cls");

	// Copying news more recent than the lastLoginDate to an ordered map
	map<string, News> orderedNews;
	set<string> preferredNews = this->getPreferredCategories();
	for (auto i = News::News_Container.begin(); i != News::News_Container.end(); i++) {
		if (i->second.getDate() > this->getLastLoginDate() && preferredNews.count(i->second.getCategory()) == 1)
			orderedNews.insert(make_pair(i->second.getDate(), i->second));
	}
	cin.ignore();

redoNotifications:
	if (!orderedNews.empty())
	{
		// Displaying the notifications (news)
		int count = 1;
		for (auto i = orderedNews.rbegin(); i != orderedNews.rend(); i++)
			cout << count++ << ". " << i->second.getTitle() << "\n   Date: " << i->second.getDate() << "\n\n";

		string selection;
		int selectionInt;
		cout << "\n\nSelect an article to display: ";
	redoArticleSelection:
		getline(cin, selection);

		// Making sure that the selection is an integer
		try {
			selectionInt = stoi(selection);
		}
		catch (exception e) {
			cout << "\nERROR: Invalid selection!\nEnter a valid number: ";
			goto redoArticleSelection;
		}

		// Checking that the selection is within range
		if (selectionInt > orderedNews.size() || selectionInt < 1) {
			cout << "\nERROR: Invalid selection!\nEnter a valid number: ";
			goto redoArticleSelection;
		}
		else {
			// Moving iterator to the selected notification
			map<string, News>::reverse_iterator it = orderedNews.rbegin();
			advance(it, selectionInt - 1);

			// Removing the selected news from notifications 
			//
			// BUG
			// 
			// Because the ordered map is local, whenever the user enters the notification menu
			// the previously checked news are visible again in the menu
			//
			News selectedNews;
			selectedNews = it->second;
			orderedNews.erase(it->second.getDate());

			if (displayNewsArticle(selectedNews)) {
				goto redoNotifications;
			}
		}
	}
	else
		cout << "\nNo new notifications!";

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
	Menus::readerMenu(*this);
}


// Searching for news
void Reader::titleSearch()
{
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	string titleToView;
redo:
	cout << "\nEnter the title of the article you want to display: ";
	cin.ignore();
	getline(cin, titleToView);
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));

	if (News::News_Container.count(titleToView))
	{
		if (displayNewsArticle(News::News_Container[titleToView]))
			goto redo;
	}

flag:
	cout << "\nEnter zero when you want to back ro your menu: ";
	string choose;
	cin >> choose;
	if (choose == "0")
		Menus::readerMenu(*this);
	else
	{
		cout << "Invalide Input .... Please try again";
		goto flag;
	}
}

void Reader::keywordSearch()
{
	system("cls");
	cout << "Enter a word to search: \n";
	string keyword;
	cin.ignore();
	getline(cin, keyword);

redo:
	int numberOfArticle = 1;
	vector<int> matchingTitles;

	for (auto i = News::News_Container.begin(); i != News::News_Container.end(); ++i) {
		if (i->second.getTitle().find(keyword) != -1 ||
			i->second.getDescription().find(keyword) != -1) {
			cout << "\n" << numberOfArticle << ": " << i->second.getTitle() << "\n";
			matchingTitles.push_back(distance(News::News_Container.begin(), i));
			numberOfArticle++;
		}
	}

	if (matchingTitles.empty()) {
		cout << "No articles found matching the keyword.\n";
	}
	else {
		cout << "\nEnter the number of the article you want to read: ";
		int selected;
		cin >> selected;

		if (selected >= 1 && selected <= matchingTitles.size()) {
			auto index = matchingTitles[selected - 1];
			auto it = News::News_Container.begin();
			advance(it, index);
			/*cout << "\nTitle: " << it->second.getTitle();
			cout << "\nDescription: " << it->second.getDescription();
			cout << "\nDate: " << it->second.getDate();
			cout << "\nWritten by: " << it->second.getAdminUserName();
			displayNewsWithComments(it->second);
			cin.ignore();
			comment(it->second);*/
			if (displayNewsArticle(it->second))
				goto redo;
		}

		else {
			cout << "Invalid selection.\n";
		}
	}

flag99:
	cout << "\n1: Search for another word\n2: Back to menu\n";
	string c; cin >> c;
	if (c == "1") {
		keywordSearch();
	}
	else if (c == "2") {
		Menus::readerMenu(*this);
	}
	else {
		cout << "\nInvalid input";
		goto flag99;
	}
}

void Reader::categorySearch()
{
	// Allow User to Search By Categories
	cout << "enter the category you want \n";
	string category;
	cin.ignore();
	getline(cin, category);
	bool check = false;//to check whether the container is exist or not

redo:
	int counter = 1;
	for (auto news : News::News_Container)
	{
		if (news.second.getCategory() == category)
		{
			cout << counter << " - ";
			cout << "news title is  : " << news.second.getTitle() << endl << endl;
			check = true;//you find it
			counter++;

		}
	}
	if (check)
	{
		cout << "enter the number of news you want to see\n";
	flag:
		int choice;
		cin >> choice;
		if (choice<1 || choice>counter)
		{
			cout << "invalid value \n1-try again\n2-return to main menu\n";
		flag1:
			int choose;
			cin >> choose;
			if (choose < 1 || choose>2)
			{
				cout << "invalid value please try agian\n";
				goto flag1;
			}
			else if (choose == 1)
			{
				goto flag;
			}
			else
			{
				this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
				Menus::readerMenu(*this);
			}
		}
		else
		{
			int iterate = 1;
			for (auto news : News::News_Container)
			{
				if (news.second.getCategory() == category)
				{
					if (iterate == choice)
					{
						//	cout << " - title : " << news.second.getTitle() << endl;
						//	cout << "discription : " << news.second.getDescription() << endl;
						//	cout << "rate : " << news.second.news_rate << endl;
						//	cout << "data : " << news.second.getDate() << endl;
						//	cout << "written by : " << news.second.getAdminUserName() << endl << endl;
						//	rateNews(news.second);
						//	string selection;
						//	cout << "\n\n1. Bookmark the article\n2. Mark the article as spam";
						//	cout << "\n3. Return to news menu\n4. Return to main menu\n\nSelection: ";
						//	cin.ignore();
						//redoMenuSelection:
						//	getline(cin, selection);
						//	if (selection == "1") {
						//		// call bookmark function
						//	}
						//	else if (selection == "2") {
						//		News::News_Container[news.second.getTitle()].addSpamSet(this->getUserName());
						//	}
						//	else if (selection == "3")
						//		viewLatestNews();
						//	else if (selection == "4")
						//		Menus::readerMenu(*this);
						//	else {
						//		cout << "\nERROR: Invalid selection!\nEnter a valid number: ";
						//		goto redoMenuSelection;
						//	}
						if (displayNewsArticle(news.second))
							goto redo;
						break;
					}
					else iterate++;
				}
			}
		}

		this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
		Menus::readerMenu(*this);
	}
	else if (!check)
	{
		cout << "ERROR: Invalid category!\n1-return to main menu \n2-try again\n" << endl;
	flag2004:
		string choice;
		cin >> choice;
		if (choice.length() == 1 && choice == "1")
		{
			Menus::readerMenu(*this);
		}
		else if (choice.length() == 1 && choice == "2")
		{
			categorySearch();
		}
		else
		{
			cout << "invalid value \n1-return to main menu\n2-try again\n\n";
			goto flag2004;
		}
	}
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(3000));
	Menus::readerMenu(*this);
}

void Reader::searchByDate() {
	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	string date;
	bool validDate{};
	while (!validDate) {
		cout << "Note that the date format is \"YYYY-MM-DD\"\n";
		cout << "Enter the date of the articles you want to display: ";
		cin >> date;
		validDate = Test::isDate(date);
		if (!validDate) {
			cout << "Invalid Date. Please try again.\n";
		}
	}

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	vector<News> News_To_Display;
	// Search for articles by date
flag_display:
	int i = 0;
	for (auto view : News::News_Container) {
		if (Test::extractDate(view.second.getDate()) == date) {
			cout << i + 1 << ": " << view.second.getTitle() << endl;
			News_To_Display.push_back(view.second);
			i++;
		}
	}
	int display;
	while (true) {
		cout << "\nEnter the number of the news you want to display: ";
		cin >> display;
		if (display > 0 && display < News::News_Container.size()) {
			break;
		}
		else {
			cout << "Invalid Choice. Please try again.\n";
		}
	}
	display--;
	// Display selected news
	/*this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	system("cls");
	cout << "\nTitle: " << News_To_Display[display].getTitle() << endl;
	cout << News_To_Display[display].getDescription() << endl;
	cout << "\nCategory: " << News_To_Display[display].getCategory() << endl;
	cout << "Date: " << News_To_Display[display].getDate() << endl;
	cout << "Published by: " << News_To_Display[display].getAdminFirstName() << " " << News_To_Display[display].getAdminSecondName() << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------\n";
	displayNewsWithComments(News_To_Display[display]);
	cin.ignore();
	comment(News_To_Display[display]);
	string choice;
	while (true) {
		cout << "\n1 -> Back to News Menu\n2 -> Back to search Menu\n3 -> Back to Main Menu\n\nEnter your choice: ";
		cin >> choice;
		if (choice == "1") {
			searchByDate();
			break;
		}
		else if (choice == "2")
		{
			goto flag_display;
			break;
		}
		else if (choice == "3") {
			Menus::readerMenu(*this);
			break;
		}
		else {
			cout << "Invalid Choice. Please try again.\n";
		}
	}*/

	if (displayNewsArticle(News_To_Display[display]))
		goto flag_display;

	this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(500));
	Menus::readerMenu(*this);
}


// Extra news functionalities
void Reader::displayNewsWithComments(News news)
{
	cout << "\nComments:\n";

	if (commentsMap.find(news) != commentsMap.end()) {
		stack<string> comments = commentsMap[news];
		while (!comments.empty()) {
			// Display :(
			cout << "- " << comments.top() << "\n";
			comments.pop();
		}
	}
	else {
		// No comments 
		cout << "No comments available for this news.\n";
	}
}

void Reader::comment(News news) {
	string comment;
	cout << "Write a comment for the news '" << news.getTitle() << "'. To skip, enter '0'\n";

	while (true) {
		getline(cin, comment);
		if (comment == "0") {
			break;
		}
		else {
			if (Test::testComment(comment)) { // Check comment 
				commentsMap[news].push(comment);
				break;
			}
			else {
				cout << "\nInvalid Comment. Please Try Again.\n";
			}
		}
	}
}

void Reader::rateNews(News& news)
{
	cout << "the rate of this news is : " << news.news_rate;
	cout << "\nrete this new or type zero to skip\n";
flag:
	float rate;
	cin >> rate;
	if (rate >= 0 && rate <= 5)
	{
		//news.calcRate();
		news.newsRates[this->user_name] = rate;
		news.calcRate();
		News::News_Container[news.getTitle()].setAvgRate(news.getRate());
		cout << "the news rated successfully \n" << "the new rate is " << news.getRate() << endl;
	}
	else if (rate > 5 || rate < 0)
	{

		cout << "invalid value \n1-try again\n2-return to the your menu\n";
	flag1:
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			goto flag;
		}
		else if (choice == 2)
		{
			Menus::readerMenu(*this);
		}
		else {
			goto flag1;
		}
	}
	cin.ignore();
}

void Reader::bookmarkNews(News* news) {
	int i = 0;
	vector<News*>::iterator new_add;
	new_add = bookmarking_container.begin();
	for (; new_add != bookmarking_container.end(); ++new_add) {
		if ((*new_add)->getTitle() == news->getTitle()) {
			cout << "This new is bookmarked before, Do you want remove the bookmark ?     (y|n)\n";
			while (true) {
				string choice;
				cin >> choice;
				if (choice == "n" || choice == "N") return;
				else if (choice == "y" || choice == "Y") {
					(*new_add)->bookmarkedOrNo = false;
					bookmarking_container.erase(bookmarking_container.begin() + i);
					cout << "\nthe news bookmarked removed successfully";
					return;
				}
				cout << "Wrong choice , try again.\nEnter (y|n): ";
			}
		}
		i++;
	}
	cout << "Bookmark this new ?    (y|n)\n";
	while (true)
	{
		string choice;
		cin >> choice;
		if (choice == "n" || choice == "N") return;
		else if (choice == "y" || choice == "Y") break;
		cout << "Wrong choice , try again.\nEnter (y|n): ";
	}
	bookmarking_container.push_back(news);
	news->bookmarkedOrNo = true;
	cout << "the news bookmarked successfully";
}

void Reader::removeAllBookmarkedNewsFromNewsContainer()
{
	vector<News*>::iterator it = bookmarking_container.begin();
	for (; it != bookmarking_container.end(); it++) {
		(*it)->bookmarkedOrNo = false;
	}
}