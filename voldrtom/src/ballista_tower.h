/**
 * @file    ballista_tower.h
 * @author  voldrtom
 */

#ifndef BALLISTA_TOWER_H
#define BALLISTA_TOWER_H

#include "tower.h"

/**
 * Class that represents the ballista tower.
 */
class CBallista_tower : public CTower {
public:
/**
 * Constructor of the ballista tower
 * @param id
 * @param x position
 * @param y position
 */
	CBallista_tower (const unsigned int & ID,
					 const int & xpos,
					 const int & ypos);
/**
 *	Implicit destructor.
 */
	~CBallista_tower () {};
/**
 *	Creates shootable frames around the tower.
 */
	virtual void create_shootable_frames ();

};

#endif
