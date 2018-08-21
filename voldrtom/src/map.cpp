#include "map.h"

/*
### (Y) -width
#
#
(X) -height
*/


CMap::CMap (const int & height,
		  	const int & width,
		  	const int & money,
		  	const bool & static_way) {
	m_maxh = height;
	m_maxw = width;
	m_height = m_maxh - 3;
  	m_width = m_maxw;
  	m_money = money;
  	m_static_way = static_way;

	m_figures_alive = 0;
	m_figures_count = 0;
	m_figures_passed = 0;
	m_towers_count = 0;
	m_logs_turned = false;

	create_map();
	create_gates();
}

CMap::CMap (const int & height,
			const int & width,
			const int & money,
			const unsigned int & passed,
			const int & alive,
			const bool & static_way,
			const int & figures_count,
			const std::vector<std::shared_ptr<CFigure>> figures,
			const int & towers_count,
			const std::vector<std::shared_ptr<CTower>> towers)
	: m_figures(figures), m_towers(towers) {
  	m_maxh = height;
  	m_maxw = width;
  	m_height = m_maxh - 3;
  	m_width = m_maxw;
  	m_money = money;
  	m_figures_passed = passed;
  	m_figures_alive = alive;
  	m_static_way = static_way;
  	m_figures_count = figures_count;
  	m_towers_count = towers_count;

	m_logs_turned = false;

  	create_map();
  	create_gates();
}


void CMap::print_map () const {
	clear();
	print_walls();
	print_towers();
	print_figures();
}

void CMap::print_walls () const {
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			
			if (m_map[i][j] == 1) {
				move(i, j);
				addch(WALL_SIGN);
			}
		}
	}

	//print gates
	move(m_start_gate.first, m_start_gate.second);
	addch(GATE_SIGN);
	move(m_exit_gate.first, m_exit_gate.second);
	addch(GATE_SIGN);

	move(m_height+1, 1);
	printw("T - build tower  S - save  Q - quit  L - logs");
	move(m_height+2, 1);
	printw("Money: %d", m_money);
}

void CMap::print_towers () const {
	for (unsigned int i = 0; i < m_towers.size(); ++i) {
		move(m_towers.at(i)->get_xpos(), m_towers.at(i)->get_ypos());
		if (m_towers.at(i)->get_type() == 0)
			addch(ARCHER_SIGN);
		else
			addch(BALLISTA_SIGN);
	}
}

void CMap::print_figures () const {
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);

	for (unsigned int i = 0; i < m_figures.size(); ++i) {
		move(m_figures.at(i)->get_xpos(), m_figures.at(i)->get_ypos());
		if (m_figures.at(i)->get_took_hit()) {
			attron(COLOR_PAIR(1));
			m_figures.at(i)->set_took_hit(false);
		}
		if (m_figures.at(i)->get_xpos() == m_exit_gate.first &&
			m_figures.at(i)->get_ypos() == m_exit_gate.second) {
			attroff(COLOR_PAIR(1));
			continue;
		}
		if (m_figures.at(i)->is_alive()) {
			if (m_figures.at(i)->get_type() == 0)
				addch(LIGHT_SIGN);
			else
				addch(MEDIUM_SIGN);
		}
		else {
			addch(DEAD_SIGN);
		}
		attroff(COLOR_PAIR(1));
	}
	
}

int CMap::get_money () const {
	return m_money;
}

void CMap::set_money (const int & money) {
	m_money = money;
}

void CMap::add_money (const int & money) {
	m_money += money;
}


void CMap::next_round () {
	clear();
	move_figures();
	check_collisions();
	print_map();

	if (m_log.size() > 0 && m_logs_turned)
		print_log();
	else
		while(!m_log.empty())
			m_log.pop();
}


void CMap::check_collisions () {
	delete_figures();
	for (unsigned int i = 0; i < m_towers.size(); ++i) {
		for (unsigned int j = 0; j < m_figures.size(); ++j) {
			if (m_towers.at(i)->is_in_range(m_figures.at(j)->get_xpos(),
											m_figures.at(j)->get_ypos())) {
				m_figures.at(j)->take_hit(m_towers.at(i)->get_type());
				m_figures.at(j)->set_took_hit(true);
				add_log(m_figures.at(j)->get_id(), m_figures.at(j)->get_health());
				break;
			}
		}
	}
}

void CMap::delete_figures () {
	for (unsigned int i = 0; i < m_figures.size(); ++i) {
		if (!m_figures.at(i)->is_alive()) {
			if (m_figures.at(i)->get_type() == 0)
				m_money += LIGHT_REWARD;
			if (m_figures.at(i)->get_type() == 1)
				m_money += MEDIUM_REWARD;

			m_figures.erase(m_figures.begin()+i);
			m_figures_alive --;
			break;
		}
	}
	for (unsigned int i = 0; i < m_figures.size(); ++i) {
		if (m_figures.at(i)->get_passed()) {
			m_figures.erase(m_figures.begin()+i);
			m_figures_passed ++;
			m_figures_alive --;
			break;
		}
	}

}

void CMap::move_figures () {

	for (unsigned int i = 0; i < m_figures.size(); ++i) {
		if (!m_static_way && 
			m_map[m_figures.at(i)->get_xpos()][m_figures.at(i)->get_ypos()] != 3) {
			m_map[m_figures.at(i)->get_xpos()][m_figures.at(i)->get_ypos()] = 0;
		}

		if (m_figures.at(i)->get_realpos() != 0) {
			if (m_figures.at(i)->get_xpos() != m_way[m_figures.at(i)->get_realpos()-1].first ||
				 m_figures.at(i)->get_ypos() != m_way[m_figures.at(i)->get_realpos()-1].second) {
				for (unsigned int j = 0; j < m_way.size(); ++j) {
					if (m_figures.at(i)->get_xpos() == m_way[j].first &&
						m_figures.at(i)->get_ypos() == m_way[j].second) {
						m_figures.at(i)->set_realpos(j+1);
						break;
					}
				}
			}
		}
		m_figures.at(i)->move(m_way[m_figures.at(i)->get_realpos()].first, m_way[m_figures.at(i)->get_realpos()].second);
		m_figures.at(i)->inc_realpos();


		if (m_figures.at(i)->get_xpos() == m_exit_gate.first &&
			m_figures.at(i)->get_ypos() == m_exit_gate.second) {
			m_figures.at(i)->set_passed(true);
		}

		if (!m_static_way &&
			m_map[m_figures.at(i)->get_xpos()][m_figures.at(i)->get_ypos()] != 3) {
			m_map[m_figures.at(i)->get_xpos()][m_figures.at(i)->get_ypos()] = 2;
		}
	}

}

void CMap::find_way () {
	std::vector<std::pair<int, int>> tmp_way;
	tmp_way.push_back(std::make_pair(m_start_gate.first, m_start_gate.second-1));
	bool done = false;
	std::pair<int, int> tmp_pos = tmp_way[0];
	std::pair<int, int> tmp_dir = std::make_pair(0,-1);

	bool main_way = true;
	int main_way_y_coord_if_i_brake;


	do {
		//Going main way
		if (main_way){
			if (m_map[tmp_pos.first+tmp_dir.first][tmp_pos.second+tmp_dir.second] != 1) {
				tmp_pos.first = tmp_pos.first+tmp_dir.first;
				tmp_pos.second = tmp_pos.second+tmp_dir.second;
				tmp_way.push_back(tmp_pos);
			} else {
				//turning
				int tmp;
				tmp = tmp_dir.first;
				tmp_dir.first = tmp_dir.second;
				tmp_dir.second = -tmp;	
				main_way = false; 
				main_way_y_coord_if_i_brake = tmp_pos.second;
			}
		 } else {
		 	//turning back to main way
		 	if (tmp_pos.first == m_exit_gate.first && main_way_y_coord_if_i_brake > tmp_pos.second){
		 		main_way = true;
				tmp_dir = std::make_pair(0,-1);
		 	} else {
		 		//turning
				if (m_map[tmp_pos.first-tmp_dir.second][tmp_pos.second+tmp_dir.first] != 1) {
					tmp_pos.first = tmp_pos.first-tmp_dir.second;
					tmp_pos.second = tmp_pos.second+tmp_dir.first;
					tmp_way.push_back(tmp_pos);

					int tmp;
					tmp = tmp_dir.first;
					tmp_dir.first = -tmp_dir.second;
					tmp_dir.second = tmp;	
				// going in turned
				} else if (m_map[tmp_pos.first+tmp_dir.first][tmp_pos.second+tmp_dir.second] != 1) {
						tmp_pos.first = tmp_pos.first+tmp_dir.first;
						tmp_pos.second = tmp_pos.second+tmp_dir.second;
						tmp_way.push_back(tmp_pos);
				// turning
				} else {
					int tmp;
					tmp = tmp_dir.first;
					tmp_dir.first = tmp_dir.second;
					tmp_dir.second = -tmp;	
					main_way = false; 
				}
			}
		}		
		if (tmp_pos.first == m_exit_gate.first &&
			tmp_pos.second-1 == m_exit_gate.second){
			done = true;
		}
	} while (!done);
	tmp_way.push_back(m_exit_gate);

	m_way.clear();

	//shorting the way by finding duplicits
	for (unsigned int i = 0; i < tmp_way.size(); ++i) {
		for (unsigned int j = i+1; j < tmp_way.size(); ++j) {
			if (tmp_way[i] == tmp_way[j]) {
				i = j;
				break;
			}
		}
		m_way.push_back(tmp_way[i]);
	}
	//marks way in map if the way is static
	if (m_static_way) {
		for (unsigned int i = 0; i < m_way.size(); ++i) {
			m_map[m_way[i].first][m_way[i].second] = 3;
		}
	}
}


void CMap::add_log (const int & id,
					const int & health) {
	m_log.push(CText_log(id, health));
}


void CMap::print_log () {
	while (!m_log.empty()) {
		move(m_height, 1);
		if (m_log.front().figurehp < 1)
			printw("Figure with ID %d was hit and died.           L - Turn off/on logs", m_log.front().figureid);
		else
			printw("Figure with ID %d was hit and has got %d hp.  L - Turn off/on logs", m_log.front().figureid, m_log.front().figurehp);
		refresh();
		tick();
		m_log.pop();
	}
}


void CMap::create_map () {
	for (int i = 0; i < m_height; ++i) {
		std::vector<int> tmp_row;
		for (int j = 0; j < m_width; ++j) {
			if (i == 0 || j ==0 ||
				i == m_height-1 ||
				j == m_width-1) {
				tmp_row.push_back(1);
			}else if (i == 1 || j == 1 ||
					 i == m_height-2 ||
					 j == m_width-2)
				tmp_row.push_back(3);
			else 
				tmp_row.push_back(0);
		}
		m_map.push_back(tmp_row);
	}
}

void CMap::add_wall (const int & x,
					 const int & y) {
	m_map[x][y] = 1;
	m_walls.push_back(std::make_pair(x,y));
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (i == 0 && j == 0) continue;
			if (m_map.at(x+i).at(y+j) == 0) {
				m_map.at(x+i).at(y+j) = 3;
			}
		}
	}
}

void CMap::create_gates () {
	m_start_gate = std::make_pair(m_height/2, m_width-1);
	m_exit_gate = std::make_pair(m_height/2, 0); 
}

void CMap::make_tower () {
	clear();
	char choice;
	move (m_maxh/2, m_maxw/2 - 15);
	printw("What kind of tower do you want to build?");
	move (m_maxh/2+1, m_maxw/2 - 6);
	printw("A - Archer tower");
	move (m_maxh/2+2, m_maxw/2 - 6);
	printw("B - Ballista tower");
	refresh();	
	nodelay(stdscr, false);
	choice = getch();
	nodelay(stdscr, true);


	move (m_maxh/2+3, m_maxw/2 - 25);

	int x = m_height/2;
	int y = m_width/2;

	if (((choice == 'A' || choice == 'a') && m_money < ARCHER_PRICE) ||
		((choice == 'B' || choice == 'b') && m_money < BALLISTA_PRICE)) {
		clear();
		move (m_maxh/2, m_maxw/2 - 15);
		printw("Not enough gold, my lord.");
		tick();
		return;
	}

	if (!(choice == 'A' || choice == 'B' ||
		  choice == 'a' || choice == 'b')) {
		clear();
		move (m_maxh/2, m_maxw/2 - 20);
		printw("Wrong choice, do you want to try again? y/n");
		while (true) {
			choice = getch();
			if (choice == 'y' ||
				choice == 'Y') {
				make_tower();
				return;				
			}
			if (choice == 'N' ||
				choice == 'n')
				return;
		}
		tick();
	} else {		
		int move_choice;
		keypad(stdscr, true);
		while (true) {
			clear();
			print_map();
			move(m_height, 1);
			printw("Where do you want to build the tower?  %d %d  (exit with key q)", x, y);

			move(x, y);
			attron(A_REVERSE);
			printw(" ");
			attroff(A_REVERSE);
			refresh();

			move_choice = getch();
			switch (move_choice) {
				case KEY_UP:
					x --;
					if (x == 0)
						x = 1;
					break;
				case KEY_DOWN:
					x ++;
					if (x == m_height-1)
						x = m_height-2;
					break;
				case KEY_RIGHT:
					y ++;
					if (y == m_width-1)
						y = m_width-2;
					break;
				case KEY_LEFT:
					y --;
					if (y == 0)
						y = 1;
					break;
				default:
					break;
			}
			if (move_choice == 10) {
				if (!can_be_placed(x,y)) {
					move(m_height+1, 1);
					printw("Wrong place, try again. (click anything to continue)");
					tick();
					continue;
				}
				else 
					break;
			}
			if (move_choice == (int)'q' ||
				move_choice == (int)'Q')
				return;
		}

		if (choice == 'A' || choice == 'a') {
			create_tower(m_towers_count, x, y, 0);
		}
		if (choice == 'B' || choice == 'b') {
			create_tower(m_towers_count, x, y, 1);
		}

	}
	clear();
}

void CMap::create_tower (const int & ID,
						 const int & xpos,
						 const int & ypos,
						 const int & type) {
	CTower * tower;
	if (type == 0) {
		tower = new CArcher_tower(ID, xpos, ypos);
		m_money -= ARCHER_PRICE;
	}
	else /*if (type == 1)//*/{	
		tower = new CBallista_tower(ID, xpos, ypos);
		m_money -= BALLISTA_PRICE;
	}

	m_towers.push_back(std::shared_ptr<CTower> (tower));
	
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (i == 0 && j == 0) continue;
			if (m_map.at(xpos+i).at(ypos+j) == 0) {
				m_map.at(xpos+i).at(ypos+j) = 3;
			}
		}
	}
	m_map.at(xpos).at(ypos) = 1;
	m_towers_count ++;

	find_way();
}


bool CMap::can_be_placed (const int & xpos,
						  const int & ypos) {
	return  !m_map.at(xpos).at(ypos);
}

bool CMap::all_passed_or_died () const {
	for (unsigned int i = 0; i < m_figures.size(); ++i) {
		if (!m_figures.at(i)->get_passed() &&
			m_figures.at(i)->is_alive()) {
			return false;
		}
	}
	return true;
}

unsigned int CMap::get_figures_passed () const {
	return m_figures_passed;
}

int CMap::get_figures_alive () const {
	return m_figures_alive;
}

void CMap::end_game (const int & value) const {
	
	if (value > 0) {
		move (m_maxh/2, m_maxw/2 - 6);
		attron(A_BOLD);
		printw("Victory!!");
		attroff(A_BOLD);
	} else if (value < 0) {
		move (m_maxh/2, m_maxw/2 - 5);
		attron(A_BOLD);
		printw("Defeat.");
		attroff(A_BOLD);

	}
	if (value != 0) {
		move (m_maxh/2+1, m_maxw/2 - 10);
		printw("Press Q to quit.");
		refresh();
		while (true) {
			char c;
			nodelay(stdscr, false);
			c = getch();
			nodelay(stdscr, true);	
			if (c == 'q' || c == 'Q')
				break;
		}
	}
}

void CMap::add_figure (CFigure * figure) {
	m_figures.push_back(std::shared_ptr<CFigure> (figure));
	m_figures_alive ++;
}

std::pair<int,int> CMap::get_start_gate () const {
	return m_start_gate;
}

bool CMap::get_way () const {
	return m_static_way;
}

void CMap::tick () const {
	nodelay(stdscr, false);
	getch();
	nodelay(stdscr, true);
}

void CMap::turn_logs () {
	m_logs_turned = !m_logs_turned;
}
