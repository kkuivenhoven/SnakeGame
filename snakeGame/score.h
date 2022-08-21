#ifndef _SCORE_H_
#define _SCORE_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Score {
	int m_flowersHit;
	int m_finalScore;

	public:
		Score();
		void initScore();
		void incrementFlowersHit();
		void wallsHit();
		
		void calculateScore();
		int getScore();	
		void writeToFile();
		// vector<int> getHighestScore();
		// vector<string> getHighestScore();
		map<int, string> getHighestScore();
};

#endif


