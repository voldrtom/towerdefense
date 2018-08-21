/**
 *  @file    menu.h
 *  @author  voldrtom
 */

#ifndef MENU_H
#define MENU_H


#include <ncurses.h>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>

#include "game.h"


/**
 * The main control panel, which opens right after running the game.
 */
class CMenu {
public:
/**
 * Implicit constructor of the menu.
 */
	CMenu ();
/**
 * Implicit destructor.
 */
	~CMenu ();
/**
 * Prints the menu and reads the player's option.
 */
	void open_menu ();
/**
 * Starts new game with default values.
 */
	void game ();
/**
 * Reads the name of the file.
 */
	void load ();
/**
 * Prints about game tower defense and about this version.
 */
	void info ();
/**
 * Prints the welcome screen.
 */
	void welcome_screen ();
/**
 * Exits the game with ending screen.
 */
	void exit ();
/**
 * Waits for player's input.
 */
	void tick () const;

private:
	//! max x of the terminal
	int m_xmax;
	//! max y of the terminal
	int m_ymax;
	//! pointer at the game, which is going to be started
	CGame * m_game;
};




#endif
