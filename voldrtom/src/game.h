/**
 * @file    game.h
 * @author  voldrtom
 */

#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <algorithm>
#include <memory>
#include <queue>
#include <utility>
#include <string>
#include <cstring>
#include <cstdlib>

#include "map.h"

#define MONEY_CONST 2000
#define FIRST_THREE_FIGURES 3
#define DYNAMIC_WAY false
#define STATIC_WAY true
#define WAY_TYPE DYNAMIC_WAY

/**
 * This class is representing the whole game and its procces.
 * In this file, user comunicate with the game.
 */

class CGame {
public:

/**
* Implicit constructor of the CGame.
*/
	CGame ();
/**
* Destructor, which destructs the map in game. 
*/
	virtual ~CGame ();

/**
* Initializes new game. 
*/
	void new_game ();
/**
* Loads a game from a file.
* @param ifstream loading file 
*/
	void load_game (std::ifstream & file);
/**
* Saves the game.
* @param string name of the file
*/
	void save_game (const std::string & file_name);
/**
* Starts the game after initializating.
*/
	void start_game ();
/**
* Creates a new figure into the queue, which will be send into the game.
* @param int type of the figure
*/
	void create_figure (const int & type);
/**
* Next round of the game.
*/
	void next_round ();
/**
* Sets the number of how many figures can pass the exit gate.
*/
	void set_goal ();
/**
* Checks the game state.
* @return int 0 if game is going, 1 if the player has won and -1 if the player has lost.
*/
	int check_game_state ();
/**
* Waits for users input. 
*/
	void tick () const;
/**
* Checks if the generated wall is valid.
* @param int x position and int y position
* @return bool if is valid
*/
	bool is_valid (const int & x,
				   const int & y);


protected:

	//! Representing map from class CMap.
	CMap * m_map;

	//! Max x position
	int m_xmax;

	//! Max y position
	int m_ymax;

	//! Queue of figures, that are sent to the battlefield
	std::queue<CFigure *> m_figures_queue;

	//! True if player has won
	bool m_victory;

	//! True if player has lost
	bool m_lose;

	//! Number, that indicates how many figures can pass to the exit gate,
	//! after reaching that number, the game ends with lose state of game
	unsigned int m_figures_maxpass;

	//! Number that indicates the number of rounds
	int m_count_rounds;

	//! Number that indicates the number of figures
	int m_count_figures;

};

#endif
