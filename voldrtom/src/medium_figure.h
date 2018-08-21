/**
 * @file    medium_figure.h
 * @author  voldrtom
 */

#ifndef MEDIUM_FIGURE_H
#define MEDIUM_FIGURE_H


#include "figure.h"

/**
 * Class representing medium figure.
 * It represents itself with the number 2
 */
class CMedium_figure : public CFigure {
public:
/**
 * Constructor of light figure.
 * @param ID, xpos, ypos
 */

	CMedium_figure (const unsigned int & ID,
					const int & xpos,
					const int & ypos);
/**
 * Implicit destructor.
 */
	~CMedium_figure () {}	
/**
 * Here is counted, how much damage does the figure gets.
 * @param int type of the tower, which shot the figure
 */
	virtual void take_hit (const int & tower_type);

};

#endif
