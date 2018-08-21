/**
 * @file    light_figure.h
 * @author  voldrtom
 */

#ifndef LIGHT_FIGURE_H
#define LIGHT_FIGURE_H

#include <utility>

#include "figure.h"

/**
 * Class representing light figure.
 * It represents itself with the number 1
 */
class CLight_figure : public CFigure {
public:
/**
 * Constructor of light figure.
 * @param ID, xpos, ypos
 */
	CLight_figure ( const unsigned int & ID,
					const int & xpos,
					const int & ypos);
/**
 * Implicit destructor.
 */
	~CLight_figure () {}	
/**
 * Here is counted, how much damage does the figure gets.
 * @param int type of the tower, which shot the figure
 */
	virtual void take_hit (const int & tower_type);

};

#endif
