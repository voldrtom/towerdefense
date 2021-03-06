#include "archer_tower.h"



CArcher_tower::CArcher_tower ( const unsigned int & ID,
							   const int & xpos,
							   const int & ypos)
	: CTower(ID, xpos, ypos, 0) {
	create_shootable_frames();
}


void CArcher_tower::create_shootable_frames () {
	std::pair<int, int> tmp_pair;

	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (i == 0 && j == 0) continue;
			tmp_pair = std::make_pair(m_xpos+i, m_ypos+j);
			m_shootable_frames.push_back(tmp_pair);
		}
	}
}
