#ifndef _SCORE_H_
#define _SCORE_H_

#include <iostream>
using namespace std;

class Score {
	int m_flowersHit;
	int m_finalScore;

	public:
		Score();
		void incrementFlowersHit();
		void wallsHit();
		
		void calculateScore();
		int getScore();	
};

#endif


