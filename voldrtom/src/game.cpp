#include "game.h"

CGame::CGame ()
	:m_victory(false), m_lose(false), m_figures_maxpass(0), m_count_rounds(0),
	 m_count_figures(0) {
	initscr();
	endwin();
}	

CGame::~CGame () {
	delete m_map;
}

bool CGame::is_valid (const int & x,
					  const int & y) {
	int counter = 0;
	for (int i = 0; i < m_xmax-3; ++i) {
		if (m_map->m_map[i][y] == 1) {
			counter ++;
		}
	}
	if (counter >= m_xmax-3-2) {
		return false;
	}
	counter = 0;
	for (int i = 0; i < m_ymax; ++i) {
		if (m_map->m_map[x][i] == 1) {
			counter ++;
		}
	}
	if (counter >= m_ymax-2) {
		return false;
	}

	if ((m_map->get_start_gate().first == x &&
		m_map->get_start_gate().second -1 == y) ||
		(m_map->get_start_gate().first == x &&
		 y == 1)) {
		return false;
	}

	return true;
}

//starts new map with defalut settings
void CGame::new_game () {
	clear();
	getmaxyx(stdscr, m_xmax, m_ymax);

	m_map = new CMap (m_xmax, m_ymax, MONEY_CONST, WAY_TYPE);

	int walls_max =  40 + (rand() % ((((m_xmax-3)*m_ymax)/8)-40));
	int walls_counter = 0;
	do {
		int rnd1 = rand() % (m_xmax-3);
		int rnd2 = rand() % m_ymax;

		if (m_map->m_map[rnd1][rnd2] != 1) {
			if (is_valid(rnd1, rnd2)) {
				walls_counter ++;
				m_map->add_wall(rnd1, rnd2);
			}
		}

	} while (walls_counter < walls_max);


	for (int i = 0; i < FIRST_THREE_FIGURES; ++i) {
		create_figure(0);
	}
	for (int i = 0; i < (m_ymax/2 + rand()%15); ++i) {
		create_figure(rand()%2);
	}

	m_map->find_way();
	set_goal();
	start_game();
}

void CGame::load_game (std::ifstream & file) {
	bool tmp_static_way;
	int tmp_xmax, tmp_ymax, tmp_money, tmp_passed, tmp_alive;
	int tmp_count_walls, tmp_count_figures, tmp_count_queue, tmp_count_towers;
	char tmp_char;
	getmaxyx(stdscr, m_xmax, m_ymax);

	if (!(file >> tmp_xmax >> tmp_ymax >> tmp_money >> tmp_passed >> tmp_alive >> tmp_static_way >> m_figures_maxpass >> m_count_rounds)) {
		clear();
		move(3, 3);
		printw("The header of the file is not correct.");
		tick();
		return;
	}
	if (tmp_ymax != m_ymax ||
		tmp_xmax != m_xmax) {
		clear();
		move(3, 3);
		printw("The resolution does not match.");
		tick();
		return;	
	}

	file >> tmp_char >> tmp_count_walls;

	std::vector<std::pair<int, int>> tmp_walls;
	for (int i = 0; i < tmp_count_walls; ++i) {
		std::pair<int,int> tmp_wall;
		file >> tmp_wall.first >> tmp_wall.second;
		tmp_walls.push_back(tmp_wall);
	}

	file >> tmp_char >> tmp_count_figures;

	
	std::vector<std::shared_ptr<CFigure>> tmp_figures;
	for (int i = 0; i < tmp_count_figures; ++i) {
		unsigned int tmp_id;
		int tmp_xpos, tmp_ypos, tmp_type, tmp_health, tmp_realpos;
		CFigure * tmp_figure;
		file >> tmp_id >> tmp_xpos >> tmp_ypos >> tmp_type >> tmp_health >> tmp_realpos;
		if (tmp_type == 0) {
			tmp_figure = new CLight_figure (tmp_id, tmp_xpos, tmp_ypos);
		} else {
			tmp_figure = new CMedium_figure (tmp_id, tmp_xpos, tmp_ypos);
		}
		tmp_figure->set_health(tmp_health);
		tmp_figure->set_realpos(tmp_realpos);
		tmp_figures.push_back(std::shared_ptr<CFigure> (tmp_figure));
	}

	file >> tmp_char >> tmp_count_queue;

	std::queue<int> tmp_queue;
	for (int i = 0; i < tmp_count_queue; ++i) {
		int tmp_type;
		file >> tmp_type;
		tmp_queue.push(tmp_type);
	}

	file >> tmp_char >> tmp_count_towers;

	std::vector<std::shared_ptr<CTower>> tmp_towers;
	for (int i = 0; i < tmp_count_towers; ++i) {
		unsigned int tmp_id;
		int tmp_xpos, tmp_ypos, tmp_type;
		file >> tmp_id >> tmp_xpos >> tmp_ypos >> tmp_type;
		CTower * tmp_tower;
		if (tmp_type == 0) {
			tmp_tower = new CArcher_tower (tmp_id, tmp_xpos, tmp_ypos);
		} else {
			tmp_tower = new CBallista_tower (tmp_id, tmp_xpos, tmp_ypos);
		}
		tmp_towers.push_back(std::shared_ptr<CTower> (tmp_tower));
	}

	if (tmp_char != 'T') {
		clear();
		move(3, 3);
		printw("An error has occured.");
		tick();
		return;
	}

	m_map = new CMap (m_xmax, m_ymax, tmp_money, tmp_passed, tmp_alive, tmp_static_way,
					  tmp_count_figures, tmp_figures, tmp_count_towers, tmp_towers);


	for (int i = 0; i < tmp_count_walls; ++i) {
		m_map->add_wall(tmp_walls[i].first, tmp_walls[i].second);
	}


	while (!tmp_queue.empty()) {
		create_figure(tmp_queue.front());
		tmp_queue.pop();
	}

	m_map->find_way();

	clear();
	move(3,3);
	printw("Game succsefully loaded. \n");
	tick();

	start_game();
}



void CGame::save_game (const std::string & file_name) {
	std::ofstream save_file;
	save_file.open(file_name);

	save_file << m_xmax << " " << m_ymax << " " << m_map->get_money() << " " << m_map->get_figures_passed() << " ";
	save_file << m_map->get_figures_alive() << " " << m_map->get_way() << " " << m_figures_maxpass << " " << m_count_rounds << "\n";

	save_file << "W " << m_map->m_walls.size();
	// if (m_map->m_walls.size() > 0) 
		save_file << "\n";
	for (unsigned int i = 0; i < m_map->m_walls.size(); ++i) {
		save_file << m_map->m_walls[i].first << " " << m_map->m_walls[i].second << "\n";
	}

	save_file << "F " << m_map->m_figures.size();
	if (m_map->m_figures.size() > 0)
		save_file << "\n";
	for (unsigned int i = 0; i < m_map->m_figures.size(); ++i) {
		save_file << m_map->m_figures.at(i)->get_id() << " " << m_map->m_figures.at(i)->get_xpos() << " ";
		save_file << m_map->m_figures.at(i)->get_ypos() << " " << m_map->m_figures.at(i)->get_type() << " ";
		save_file << m_map->m_figures.at(i)->get_health() << " " << m_map->m_figures.at(i)->get_realpos() << "\n";
	}

	std::queue<CFigure *> tmp_queue;
	save_file << "Q " << m_figures_queue.size();
	if (m_figures_queue.size() > 0)
		save_file << "\n";
	while (!m_figures_queue.empty()) {
		save_file << m_figures_queue.front()->get_type() << " ";
		tmp_queue.push(m_figures_queue.front());
		m_figures_queue.pop();
	} save_file << "\n";
	m_figures_queue = tmp_queue;


	save_file << "T " << m_map->m_towers.size();
	save_file << "\n";
	for (unsigned int i = 0; i < m_map->m_towers.size(); ++i) {
		save_file << m_map->m_towers.at(i)->get_id() << " " << m_map->m_towers.at(i)->get_xpos() << " ";
		save_file << m_map->m_towers.at(i)->get_ypos() << " " << m_map->m_towers.at(i)->get_type() << "\n";
	}

	save_file.close();

	clear();
	move(m_xmax/2, m_ymax/2 - 8);
	printw("Game saved.");
}

void CGame::start_game () {
	m_map->print_map();
	while (true) {
		char choice;
		refresh();

		nodelay(stdscr, false);
		choice = getch();

		if ((int)choice == 10) {
			next_round ();
			m_map->next_round();
			m_count_rounds ++;

			if (m_map->get_figures_passed() == m_figures_maxpass)
				m_lose = true;
			if (m_map->all_passed_or_died()) 
				m_victory = true;
			m_map->end_game(check_game_state());
			if (check_game_state() != 0)
				break;	
		}

		
		if (choice == 't' ||
			choice == 'T') {
			m_map->make_tower();
			m_map->print_map();
			refresh();
		}

		if (choice == 'L' || choice == 'l')
			m_map->turn_logs();

		if (choice == 'q' ||
			choice == 'Q') {
			while (true) {
				clear();
				move(m_ymax/2, m_xmax/2 - 15);
				printw("Are you sure that you want to exit? y/n");
				choice = getch();
				if (choice == 'Y' ||
					choice == 'y')
					return;
				if (choice == 'N' ||
					choice == 'n')
					break;
			}
		}
		if (choice == 'S' ||
			choice == 's') {

			while (true) {
				char file_name[50];
				clear();
				move(3, 3);
				printw("Write down name, how your save file should be named. (max 50 characters)");
				move(4, 3);
				curs_set(1);
				echo();
				getstr(file_name);
				curs_set(0);
				noecho();
				refresh();
				std::ifstream check_file(file_name);
				if (std::string(file_name) == "") {
					move(5,3);
					printw("File name have to be at least one letter.");
					getch();
				} else if (check_file.good()) {
					check_file.close();
					move(5, 3);
					printw("This file already exists. Try another one.");
					getch();	
				} else {
					std::string file(file_name);
					save_game(file);
					break;
				}
			}
			nodelay(stdscr, true);

		}
	}
}

void CGame::set_goal () {
	m_figures_maxpass = m_figures_queue.size()/4+1;
}

void CGame::create_figure (const int & type) {
	CFigure * figure;
	std::pair<int, int> start_gate = m_map->get_start_gate();
	switch (type) {
		case 0:
			figure = new CLight_figure(m_count_figures, start_gate.first, start_gate.second);
			break;
		case 1:
			figure = new CMedium_figure(m_count_figures, start_gate.first, start_gate.second);
			break;
		default:
			break;
	}
	m_count_figures ++;
	m_figures_queue.push(figure);
}

void CGame::next_round () {
	if ((m_count_rounds % 20) > 2+(rand()%6)) return;
	if (m_figures_queue.empty()) return;
	m_map->add_figure(m_figures_queue.front());
	m_figures_queue.pop();
	
}


int CGame::check_game_state () {
	if (m_lose) return -1;
	if (m_victory) return 1;
	return 0;
}

void CGame::tick () const {
	nodelay(stdscr, false);
	getch();
	nodelay(stdscr, true);
}
