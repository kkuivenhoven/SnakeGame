#include "score.h"

Score::Score() { }

void Score::initScore() {
	m_flowersHit = 0;
	m_finalScore = 0;
}

void Score::incrementFlowersHit() {
	m_flowersHit += 1;
}

void Score::calculateScore() {
	m_finalScore = (m_flowersHit * 1);
}

int Score::getScore() {
	return m_flowersHit;
}

void Score::writeToFile() {
	calculateScore();
	int finalScore = getScore();
	string finalScore_str = to_string(finalScore);
	fstream scoreFile;
	scoreFile.open("scoreKeeper.csv", ios_base::app | ios_base::in);
	time_t now = time(0);
	char *dateTime = ctime(&now);

	time_t rawtime;
	struct tm *timeinfo;
	char buffer[11];
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);

  strftime(buffer, 11, "%m/%d/%Y", timeinfo); 
	string finalizedDate(buffer);
		
	if(scoreFile.is_open()) {
		scoreFile << finalScore_str;
		scoreFile << ",";
		scoreFile << finalizedDate;
		scoreFile << "\n";
	}
	scoreFile.close();
}

map<int, string> Score::getHighestScore() {
	map<int, string> scores;

	ifstream infile("scoreKeeper.csv");
	string line;
	while(getline(infile, line)) {
		string scoreStr;
		string dateStr;
		bool hasCommaBeenReached = false;
		for(std::string::size_type i = 0; i < line.size(); i++) {
			if(hasCommaBeenReached == false) {
				scoreStr.push_back(line[i]);	
			} else {
				dateStr.push_back(line[i]);	
			}
			if(line[i] == ',') {
				hasCommaBeenReached = true;
			} 
		}
		int score = stoi(scoreStr);
		scores.insert(pair<int, string>(score, dateStr));
	}

	return scores;
}
