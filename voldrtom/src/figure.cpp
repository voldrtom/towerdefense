#include "figure.h"

CFigure::CFigure (const unsigned int & ID,
				  const int & xpos,
				  const int & ypos,
				  const int & type,
				  const int & health)
	: m_id(ID), m_xpos(xpos), m_ypos(ypos),
	  m_type(type), m_health(health), m_passed(false),
	  m_took_hit(false), m_realpos(0) {}

bool CFigure::is_alive () const {
	if (m_health > 0) return true;
	return false;
}

int CFigure::get_xpos () const {
	return m_xpos;
}

int CFigure::get_ypos () const {
	return m_ypos;
}

unsigned int CFigure::get_id () const {
	return m_id;
}

int CFigure::get_health () const {
	return m_health;
}

void CFigure::set_health (const int & health) {
	m_health = health;
}

int CFigure::get_type () const {
	return m_type;
}

bool CFigure::get_passed () const {
	return m_passed;
}

void CFigure::set_passed (const bool & value) {
	m_passed = value;
}

bool CFigure::get_took_hit () const {
	return m_took_hit;
}

void CFigure::set_took_hit (const bool & value) {
	m_took_hit = value;
} 

void CFigure::move (const int & x,
					const int & y) {
	m_xpos = x;
	m_ypos = y;
}

void CFigure::set_realpos (const unsigned int & realpos) {
	m_realpos = realpos;
}

unsigned int CFigure::get_realpos () const {
	return m_realpos;
}

void CFigure::inc_realpos () {
	m_realpos ++;
}
