/**
 * @file    archer_tower.h
 * @author  voldrtom
 */

#ifndef ARCHER_TOWER_H
#define ARCHER_TOWER_H

#include "tower.h"

/**
 * Class that represents the archer tower.
 */
class CArcher_tower : public CTower {
public:
/**
 * Constructor of the archer tower
 * @param id
 * @param x position
 * @param y position
 */
	CArcher_tower ( const unsigned int & ID,
					const int & xpos,
					const int & ypos);
/**
 *	Implicit destructor.
 */
	~CArcher_tower () {}
/**
 *	Creates shootable frames around the tower.
 */
	virtual void create_shootable_frames ();

};

#endif
