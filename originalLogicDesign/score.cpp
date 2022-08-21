#include "score.h"

Score::Score() {
	m_flowersHit = 0;
}

void Score::incrementFlowersHit() {
	m_flowersHit += 1;
}

void Score::calculateScore() {
	m_finalScore = (m_points + (m_flowersHit * 2));
}

int Score::getScore() {
	return m_finalScore;
}

