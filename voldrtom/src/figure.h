/**
 *  @file    figure.h
 *  @author  voldrtom
 */

#ifndef FIGURE_H
#define FIGURE_H

#include <memory>
#include <utility>

#define LIGHT_SIGN '1'
#define MEDIUM_SIGN '2'

#define DEAD_SIGN 'X'

#define LIGHT_REWARD 200
#define MEDIUM_REWARD 500

/**
 * Parent class representing a figure.
 */
class CFigure {
public:
/**
 * Constructor of parent class.
 * @param ID
 * @param xpos
 * @param ypos
 * @param type
 * @param health
 * type can be 0 - Light armsman or 1 - Medium armsman
 */
	CFigure (const unsigned int & ID,
			 const int & xpos,
			 const int & ypos,
			 const int & type,
			 const int & health);
/**
 * Implicit destructor of the figure.
 */
	virtual ~CFigure () {}
/**
 * Here is counted, how much damage does the figure gets.
 * @param int type of the tower, which shot the figure
 */
	virtual void take_hit (const int & tower_type) = 0;
/**
 * Moves with the figure to the next frame.
 * @param x position
 * @param y position
 */
	void move (const int & x,
			   const int & y);
/**
 * If the figure is alive.
 * @return true if is alive
 */
	bool is_alive () const;
/**
 * Getter for x position
 * @return x position
 */
	int get_xpos () const;
/**
 * Getter for y position
 * @return y position
 */
	int get_ypos () const;
/**
 * Getter for id
 * @return id
 */
	unsigned int get_id () const;
/**
 * Getter for health
 * @return health
 */
	int get_health () const;
/**
 * Setter for health
 * @param int health
 */
	void set_health (const int & health);
/**
 * Getter for type
 * @return type of the fiure
 * 0 - light_figure, 1 - medium_figure
 */
	int get_type () const;
/**
 * Getter if figure has passed
 * @return true if passed
 */
	bool get_passed () const;
/**
 * Setter if figure has passed
 * @param passed
 */
	void set_passed (const bool & value);
/**
 * Getter if figure took hit from tower
 * @return true if got hit
 */
	bool get_took_hit () const;
/**
 * Setter if figure took hit from tower
 * @param got hit
 */
	void set_took_hit (const bool & value);
/**
 * Setter for real position in way
 * @param real position
 */
	void set_realpos (const unsigned int & realpos);
/**
 * Increments the real position
 */
	void inc_realpos ();
/**
 * Getter for real position in way
 * @return real position
 */
	unsigned int get_realpos () const;


protected:
	//! id of the figure
	unsigned int m_id;
	//! representing x position
	int m_xpos;
	//! representing y position
	int m_ypos;
	//! value of type
	int m_type;
	//! value of health
	int m_health;
	//! true if the figure passed
	bool m_passed;
	//! true if the figure took hit
	bool m_took_hit;
	//! value of figure's real position
	unsigned int m_realpos;

};

#endif
