#include <iostream>
#include "Menus.h"
#include "io_files.h"
using namespace std;

int main()
{
	io_files::fetch_admin_data();
	io_files::fetch_news_data();
	io_files::fetch_reader_data();
	io_files::fetch_categories();
	io_files::fetch_comments_from_file();

	Menus::mainMenu();
}