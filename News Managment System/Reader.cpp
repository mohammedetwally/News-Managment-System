#include "Reader.h"
void Reader::edit_profile(Reader reader)
{
	cout << "Editing Reader Profile\n";

	// Display current profile information
	cout << "Current User Name: " << reader.user_name << endl;
	cout << "Current Password: " << reader.password << endl;
	cout << "Current First Name: " << reader.first_name << endl;
	cout << "Current Second Name: " << reader.second_name << endl;

	// Prompt user for new profile information
	cout << "Enter new User Name: ";
	getline(cin, reader.user_name);
	cout << "Enter new Password: ";
	getline(cin, reader.password);
	cout << "Enter new First Name: ";
	getline(cin, reader.first_name);
	cout << "Enter new Second Name: ";
	getline(cin, reader.second_name);

	// Display confirmation message
	cout << "Profile updated successfully!\n";
}

void Reader::viewLatestNews()
{
	// See New News (:
}

void Reader::categorySearch()
{
	// Allow User to Search By Categories
}

void Reader::keywordSearch()
{
	// Allow User to Search By KeyWords
}
