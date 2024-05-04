# include<iostream>
# include<string>
# include<map>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include"User.h"
#include"Reader.h"
#include"Admin.h"
#include"Test.h"
#include"Menus.h"
#include "io_files.h"
using namespace std;
int main()
{
	io_files::fetch_admin_data();
	io_files::fetch_reader_data();
	io_files::fetch_news_data();
	io_files::fetch_categories();

	User user;
	Menus::mainMenu(user);

	io_files::save_news_data();
	io_files::save_reader_data();
	io_files::save_admin_data();
	io_files::save_categories();
}