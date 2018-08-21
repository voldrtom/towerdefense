#include "menu.h"

CMenu::CMenu () {
	initscr();
	noecho();
	curs_set(0);
	nodelay(stdscr, true);
	start_color();
	clear();
}

CMenu::~CMenu () {
	// delete m_game;
}

void CMenu::welcome_screen () {	
	getmaxyx(stdscr,m_ymax,m_xmax);
	move (m_ymax / 2, m_xmax / 2 - 7);
	attron(A_BOLD);
	printw("Tower defense");
	attroff(A_BOLD);
	refresh();
	tick();
}

//prints the menu and reads the player's option
void CMenu::open_menu () {
	bool done = false;
	do {
		m_game = new CGame();
		clear();
		WINDOW * menuwin = newwin(m_ymax/2, m_xmax/2, m_ymax/4, m_xmax/4);
		keypad(menuwin, true);

		std::string choices[4] = {"New game", "Load game", "About", "Exit"};
		int choice;
		int highlighted = 0;

		while (1) {
			box(menuwin, 0, 0);
			refresh();
			wattron(menuwin, A_BOLD);	
			mvwprintw(menuwin, 1, m_ymax/1.5+1, "MENU"); 
			wattroff(menuwin, A_BOLD);
			wrefresh(menuwin);
			refresh();
			for (int i = 0; i < 4; ++i) {
				if (i == highlighted )
					wattron(menuwin, A_REVERSE);
				mvwprintw(menuwin, i+2, m_ymax/3, choices[i].c_str());
				wattroff(menuwin, A_REVERSE);
			}
			choice = wgetch(menuwin);
			switch (choice) {
				case KEY_UP:
					highlighted --;
					if (highlighted < 0)
						highlighted = 0;
					break;
				case KEY_DOWN:
					highlighted ++;
					if (highlighted > 3)
						highlighted = 3;
					break;
				default:
					break;
			}

			if (choice == 10)
				break;
		}
		switch (highlighted) {
			case 0:
				delwin(menuwin);
				m_game->new_game();
				clear();
				break;
			case 1:
				delwin(menuwin);
				load();
				break;
			case 2:
				delwin(menuwin);
				info();
				break;
			case 3:
				delwin(menuwin);
				exit();
				return;
			default:
				break;
		}
	} while (!done);
}


//reads the name of file
void CMenu::load () {
	clear();
	move(3,3);
	printw("Please type name of the savefile: (max 50 characters)");
	refresh();

	move(4,3);

	nodelay(stdscr, false);
	char file_name[50];
	curs_set(1);
	echo();
	getstr(file_name);
	curs_set(0);
	noecho();

	std::ifstream saved_file (file_name, std::ios::in);

	if (saved_file.is_open()) {
		m_game->load_game(saved_file);
	}
	else {
		move(5,3);
		printw("Error has occured. The file cannot be opened.");
		move(6,3);
		printw("Do you want to try again? y/n");
		refresh();
		while (1) {
			char c = getch ();
			if (c == 'Y' || c == 'y') {
				load();
				break;
			}
			if (c == 'N' || c == 'n') {
				return;
			}
		}
	}
	clear();
}

//prints about game tower defense
void CMenu::info () {
	clear();
	keypad(stdscr, true);
	box(stdscr, 0, 0);
	attron(A_BOLD);	
	mvprintw(1, m_xmax/2 - 5, "ABOUT");
	attroff(A_BOLD);
	mvprintw(2, m_xmax/2 - 12, "*press anything to exit*");
	refresh();
	move(4,3);
	printw("This game is about building towers and kill all attackers.");
	move(5,3);
	printw("You lose the game, when half of the attackers will pass.");
	move(6,3);
	printw("You win the game, when you dont let half of attackers pass.");
	move(7,3);
	printw("There are two types of attackers and two types of towers.");
	move(8,3);
	printw("If you kill an attacker, you will be rewarded.");
	move(9,3);
	printw("The value of reward is based on type of attacker.");
	move(10,3);
	printw("Build of tower costs money, better tower costs more.");
	move(11,3);
	printw("You cannot build a tower right next to another tower.");
	move(12,3);
	printw("You cannot build a tower right next to a wall.");
	move(13,3);
	printw("The figures are finding the way with right hand rule.");
	
	tick();
}


void CMenu::exit () {
	clear();
	move (m_ymax / 2, m_xmax / 2 - 10);
	attron(A_BOLD);
	printw("Thanks for playing,");
	attroff(A_BOLD);
	move (m_ymax / 2 +1, m_xmax / 2 - 8);
	printw("see you soon...");
	refresh();
	tick();
}

void CMenu::tick () const {
	nodelay(stdscr, false);
	getch();
	nodelay(stdscr, true);
}
