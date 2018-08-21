/**
 * @file    tower.h
 * @author  voldrtom
 */

#ifndef TOWER_H
#define TOWER_H

#include <memory>
#include <vector>
#include <queue>
#include <utility>
#include <iostream>

#include "figure.h"

#define ARCHER_SIGN 'A'
#define BALLISTA_SIGN 'B'

#define ARCHER_PRICE 500
#define BALLISTA_PRICE 1000



/**
 * Parent class representing a tower.
 */
class CTower {
public:
/**
 * Constructor of parent class tower.
 * @param id
 * @param x position
 * @param y position
 * @param type
 * type 0 - archer_tower or 1 - ballista_tower
 */
	CTower (const unsigned int & ID,
			const int & xpos,
			const int & ypos,
			const int & type);
/**
 * Implicit destructor of the tower .
 */
	virtual ~CTower () {}
/**
 *	Creates shootable frames around the tower.
 */
	virtual void create_shootable_frames () = 0;

/**
 * If the frame is in range of the tower
 * @param x position
 * @param y position
 * @return if is in range
 */
	bool is_in_range (const int & xpos,
					  const int & ypos);

/**
 * Getter for tower id.
 * @return tower id
 */
	int get_id () const;
/**
 * Getter for x position.
 * @return x position
 */
	int get_xpos () const;
/**
 * Getter for y position.
 * @return y position
 */
	int get_ypos () const;
/**
 * Getter for tower type.
 * @return tower type
 */
	int get_type () const;


protected:
	//! Id of tower
	int m_id;
	//! x position
	int m_xpos;
	//! y position
	int m_ypos;
	//! type of the tower
	int m_type;
	//! vector of the shootable frames
	std::vector<std::pair <int,int> > m_shootable_frames;

};

#endif
