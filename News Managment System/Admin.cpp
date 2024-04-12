#include "Admin.h"

// For Editing Admin's Exsit Data
void Admin::editProfile(Admin admin)
{
	cout << "Editing Admin Profile\n";

	// Display current profile information
	cout << "Current User Name: " << admin.user_name << endl;
	cout << "Current Password: " << admin.password << endl;
	cout << "Current First Name: " << admin.first_name << endl;
	cout << "Current Second Name: " << admin.second_name << endl;

	// Prompt user for new profile information
	cout << "Enter new User Name: ";
	getline(cin, admin.user_name);
	cout << "Enter new Password: ";
	getline(cin, admin.password);
	cout << "Enter new First Name: ";
	getline(cin, admin.first_name);
	cout << "Enter new Second Name: ";
	getline(cin, admin.second_name);

	// Display confirmation message
	cout << "Profile updated successfully!\n";
}

void Admin::addNews()
{
	// Adds The Lastest News
}

void Admin::viewNewsArticles() {
	// view news articles
}

void Admin::manageCategories() {
	// manage categories
}

void Admin::manageUsers() {
	// manage users
}

void Admin::analyticsAndReports() {
	// analytics and reports
}

void Admin::editNews()
{
	// to update or edit news
}
