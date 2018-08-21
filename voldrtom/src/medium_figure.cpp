#include "medium_figure.h"

CMedium_figure::CMedium_figure (const unsigned int & ID,
								const int & xpos,
								const int & ypos)
	: CFigure(ID, xpos, ypos, 1, 125) {}


void CMedium_figure::take_hit (const int & tower_type) {
	int damage = int((tower_type + 10) * 1.5);
	switch (tower_type) {
		case 0:
			m_health -= int(damage/2);
			break;
		case 1:
			m_health -= damage;
			break;
		default:
			break;
	}

}
