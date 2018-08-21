/**
 *  @file    map.h
 *  @author  voldrtom
 */

#ifndef MAP_H
#define MAP_H

#include <ncurses.h>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <algorithm>

#include "archer_tower.h"
#include "ballista_tower.h"
#include "light_figure.h"
#include "medium_figure.h"
#include "textlog.h"

#define WALL_SIGN '#'
#define GATE_SIGN ':'



/**
* Class, that represents a Map.
*/
class CMap {
public:
/**
* First constructor of the map. It creates new map.
* @param height
* @param width
* @param money
* @param way type
*/
	CMap (const int & height,
		  const int & width,
		  const int & money,
		  const bool & static_way);

/**
* Second constructor of the map. It creates a map from load.
* @param height
* @param width
* @param money
* @param how many figures passed
* @param how many figures are alive
* @param way type
* @param count of the figures
* @param vector of shared pointers at figures
* @param count of the towers
* @param vector of shared pointers at towers
*/
	CMap (const int & height,
		  const int & width,
		  const int & money,
		  const unsigned int & passed,
		  const int & alive,
		  const bool & static_way,
		  const int & figures_count,
		  const std::vector<std::shared_ptr<CFigure> > figures,
		  const int & towers_count,
		  const std::vector<std::shared_ptr<CTower> > towers);


/**
 * Implicit destructor of the Map.
 */
	~CMap () {}
/**
 * Main print of the map, that calls other prints of map.
 */
	void print_map () const;
/**
 * Print of the walls.
 */
	void print_walls () const;
/**
 * Print of the towers.
 */
	void print_towers () const;
/**
 * Print of the figures.
 */
	void print_figures () const;
/**
 * Getter for money.
 * @return money
 */
	int get_money () const;
/**
 * Setter for money.
 * @param money
 */
	void set_money (const int & money);
/**
 * Adds value to money after killing a figure.
 * @param money to be added
 */
	void add_money (const int & money);
/**
 * Function that calls other needed functions in round.
 */
	void next_round ();
/**
 * Checks turrets, if they can attack. If they can, they will attack.
 * Checks if any of figures won or died.
 */
	void check_collisions ();
/**
 * Adds log entity to the queue
 * @param figure's id
 * @param figure's health
 */
	void add_log (const int & id,
				  const int & health);
/**
 * Function that prints log and pops printed from the queue
 */
	void print_log ();
/**
 * Function that creates the map. Its called from the constructor.
 */
	void create_map ();
/**
 * Function that creates a tower.
 * @param id
 * @param x position
 * @param y position
 * @param type of the tower
 */
	void create_tower ( const int & ID,
						const int & xpos,
						const int & ypos,
						const int & type);
/**
 * This functions is called when the user wants to create a tower.
 * It asks the user for needed information to create a tower and calls function create_tower()
 */
	void make_tower ();
/**
 * Adds figure to the vector of shared pointers at figures
 */
	void add_figure (CFigure * figure);
/**
 * Creates gates in the middle of the map.
 */
	void create_gates ();
/**
 * Validator if the tower can be placed on that position.
 * @param x position
 * @param y position
 */
	bool can_be_placed (const int & xpos,
						const int & ypos);
/**
 * Moves with figures.
 */
	void move_figures ();
/**
 * If all figures passed or died so there is no figure at battlefield.
 * @return true if there is no figure in the battlefield
 */
	bool all_passed_or_died () const;
/**
 * Delete dead or passed figures from vector.
 */
	void delete_figures ();
/**
 * Getter for how many figures passed.
 * @return number of figures passed
 */
	unsigned int get_figures_passed () const;
/**
 * Getter for how many figures are alive.
 * @return number of figures that are alive
 */
	int get_figures_alive () const;
/**
 * If its end of the game, it prints end quotes.
 * @param number value of game state
 */
	void end_game (const int & value) const;
/**
 * Getter of start gate.
 * @param pair<int, int> of x and y position
 */
	std::pair<int,int> get_start_gate () const;
/**
 * Inserts walls from vector to map.
 */
	void insert_walls ();
/**
 * Adds a wall into the map.
 * @param x position
 * @param y position
 */
	void add_wall (const int & x,
				   const int & y);
/**
 * Algorithm, that finds the way for the figures.
 */
	void find_way ();
/**
 * Getter for type of the way
 * @return true if the way is static
 * false otherwise
 */
	bool get_way () const;
/**
* Waits for users input. 
*/
	void tick () const;
/**
* Turns logs on and off
*/
	void turn_logs ();

	//! vector of inside walls
	std::vector<std::pair<int, int> > m_walls;

	//! vector of pointers at all figures, that are moving in the map
	std::vector<std::shared_ptr<CFigure> > m_figures;

	//! vector of pointers at all towers over the map
	std::vector<std::shared_ptr<CTower> > m_towers;	

	//! map created of int numbers, 1 indicates wall, 0 indicates clear spot
	//! 2 and 3 indicates way and figures
	std::vector<std::vector<int> > m_map;


private:
	//! max x position
	int m_maxh;
	//! max y position
	int m_maxw;
	//! max x position of map
	int m_height;
	//! max y position of map
	int m_width;
	//! number of player's money
	int m_money;
	//! number, that counts figures who passed through exit_gate
	unsigned int m_figures_passed;
	//! number, that counts figures alive
	int m_figures_alive;
	//! indicates if the way is static
	bool m_static_way;
	//! number, that counts all figures
	int m_figures_count;
	//! number, that counts all towers
	int m_towers_count;
	//! indicates if logs are turned off or on
	bool m_logs_turned;
	//! saves the way for figures through the map
	std::vector<std::pair<int, int> > m_way;
	//! indicates start gate
	std::pair<int, int> m_start_gate;
	//! indicates exit gate
	std::pair<int, int> m_exit_gate;
	//! saves the added logs
	std::queue<CText_log> m_log;
};


#endif
