#include "light_figure.h"


CLight_figure::CLight_figure (const unsigned int & ID,
							  const int & xpos,
							  const int & ypos)
	: CFigure(ID, xpos, ypos, 0, 100) {}


void CLight_figure::take_hit (const int & tower_type) {
	int damage = int((tower_type + 10) * 1.5);
	switch (tower_type) {
		case 0:
			m_health -= damage;
			break;
		case 1:
			m_health -= int(damage*1.5);
			break;
		default:
			break;
	}
	
}
