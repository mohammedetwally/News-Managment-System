#include "Admin.h"
#include "Reader.h"

class Menus
{
public:
	static void mainMenu();
	static void Exit();
	static void adminMenu(Admin admin);
	static void readerMenu(Reader reader);
	static string getCurrentDate();
};