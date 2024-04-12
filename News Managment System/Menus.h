#include "Admin.h"
#include "Reader.h"

class Menus
{
public:
	static void mainMenu(User user);
	static void Exit();
	static void adminMenu(Admin admin);
	static void readerMenu(Reader reader);
};