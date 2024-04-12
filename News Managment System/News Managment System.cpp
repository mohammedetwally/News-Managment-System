# include<iostream>
# include<string>
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
#include"User.h"
#include"Reader.h"
#include"Admin.h"
#include"Test.h"
#include"Menus.h"
using namespace std;
int main()
{
	User user;
	Menus::mainMenu(user);
}