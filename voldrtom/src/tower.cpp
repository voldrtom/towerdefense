
#include "tower.h"


CTower::CTower (const unsigned int & ID,
				const int & xpos,
				const int & ypos,
				const int & type)
	: m_id(ID), m_xpos(xpos), m_ypos(ypos), m_type(type) {}


int CTower::get_id () const {
	return m_id;
}

int CTower::get_xpos () const {
	return m_xpos;
}

int CTower::get_ypos () const {
	return m_ypos;
}

int CTower::get_type () const {
	return m_type;
}

bool CTower::is_in_range (const int & xpos,
						  const int & ypos) {
	std::pair<int, int> tmp_pair = std::make_pair(xpos,ypos);
	for (unsigned int i = 0; i < m_shootable_frames.size(); ++i) {
		if (tmp_pair.first == m_shootable_frames[i].first &&
			tmp_pair.second == m_shootable_frames[i].second)
			return true;
	}
	return false;
}
