
#include "menu.h"

using namespace std;

int main (int argc, char const *argv[]) {

	 CMenu menu;
	 menu.welcome_screen();
	 menu.open_menu();

	 refresh();
	 endwin();
	

	return 0;
}
