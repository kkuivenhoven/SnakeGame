#include "player.h"

// Player::Player(WINDOW *win, int y, int x, char c) {
Player::Player() {
	/* m_curwin = win;
	m_yLoc = y;
	m_xLoc = x;
	getmaxyx(m_curwin, m_yMax, m_xMax);
	m_character = c;
	m_gameover = false; */
}

void Player::initPlayer(WINDOW *win, int y, int x, char c) {
	m_curwin = win;
	m_yLoc = y;
	m_xLoc = x;
	getmaxyx(m_curwin, m_yMax, m_xMax);
	m_character = c;
	m_gameover = false;
	m_isSnakeMovingDown = false;
	m_isSnakeMovingRight = false;
	m_isSnakeMovingLeft = false;
	m_isSnakeMovingUp = false;
	m_curScore.initScore();
	m_isInit = true;
	m_startTime = clock();
}

bool Player::isInit() { return m_isInit; }

void Player::resetAllProperties() {
	m_yLoc = 1;
	m_xLoc = 1;
	m_character = ' ';
	mvwaddch(m_curwin, m_yLoc, m_xLoc, m_character);
	m_gameover = false;
}

void Player::setSnakeCharacter() {
	m_character = '@';
}

bool Player::getGameOverBoolean() {
	return m_gameover;
}


bool Player::snakeHitFruit() {
	if((m_fruitPos.first == m_yLoc) && (m_fruitPos.second == m_xLoc)) {
		m_curScore.incrementFlowersHit();
		return true;
	}
	return false;
}


int Player::getFinalScore() {
	return m_curScore.getScore();
}


void Player::printSpace() {
	storeCoords();
	mvwaddch(m_curwin, formerSnakePrint.first, formerSnakePrint.second, ' ');
}


void Player::moveUp() {
	// coordinate system moves from top down
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_yLoc--;
	if(m_yLoc < 1) { 
		m_gameover = true;	
		// m_yLoc = 1;
	} 
	m_isSnakeMovingUp = true;
	m_isSnakeMovingDown = false;
	m_isSnakeMovingLeft = false;
	m_isSnakeMovingRight = false;
}


void Player::moveDown() {
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_yLoc++;
	if(m_yLoc > m_yMax-2) { 
		m_gameover = true;	
		// m_yLoc = m_yMax - 2;
	} 
	m_isSnakeMovingUp = false;
	m_isSnakeMovingDown = true;
	m_isSnakeMovingLeft = false;
	m_isSnakeMovingRight = false;
}


void Player::moveLeft() {
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_xLoc--;
	if(m_xLoc < 1) {
		m_gameover = true;	
		// m_xLoc = 1;
	} 
	m_isSnakeMovingUp = false;
	m_isSnakeMovingDown = false;
	m_isSnakeMovingLeft = true;
	m_isSnakeMovingRight = false;
}


void Player::moveRight() {
	// printSpace();
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_xLoc++;
	if(m_xLoc > m_xMax - 2) {
		m_gameover = true;	
		// m_xLoc = m_xMax - 2;
	} 
	m_isSnakeMovingUp = false;
	m_isSnakeMovingDown = false;
	m_isSnakeMovingLeft = false;
	m_isSnakeMovingRight = true;
}


int Player::moveSnake() {
	int choice = wgetch(m_curwin);
	switch(choice) {
		case KEY_UP:
			moveUp();
			break;
		case KEY_DOWN:
			moveDown();
			break;
		case KEY_LEFT:
			moveLeft();
			break;
		case KEY_RIGHT:
			moveRight();
			break;
		default:
			break;
	}
	return choice;
}


void Player::storeCoords() {
	if(snakeCoords.size() == 3) {
		formerSnakePrint.first = snakeCoords.at(0).first;
		formerSnakePrint.second = snakeCoords.at(0).second;
		snakeCoords.erase(snakeCoords.begin());	
	}
	std::pair<int, int> tempCoords;
	tempCoords.first = m_yLoc;
	tempCoords.second = m_xLoc;
	snakeCoords.push_back(tempCoords);
}


void Player::displaySnake() {
	mvwaddch(m_curwin, m_yLoc, m_xLoc, m_character);
	/* if(snakeCoords.size() == 3) {
		 for(std::vector<pair<int, int> >::iterator it 
			= snakeCoords.begin(); it != snakeCoords.end(); it++) {
		 mvwaddch(m_curwin, it->first, it->second, m_character);
		 }
		 } else {
		 mvwaddch(m_curwin, m_yLoc, m_xLoc, m_character);
		 } */
}


void Player::generateFruit() {
	srand((unsigned) time(0));
	int xPos_fruit = (rand() % (m_xMax-2));
	int yPos_fruit = (rand() % (m_yMax-2));
	if(yPos_fruit == 0) {
		yPos_fruit += 1;
	}
	if(xPos_fruit == 0) {
		xPos_fruit += 1;
	}
	m_fruitPos.first = yPos_fruit;
	m_fruitPos.second = xPos_fruit;
	mvwaddch(m_curwin, yPos_fruit, xPos_fruit, 'x');
}


void Player::clearFruit() {
	mvwaddch(m_curwin, m_fruitPos.first, m_fruitPos.second, ' ');
}


void Player::writeScore() {
	m_curScore.writeToFile();
}


map<int, string> Player::getHighScores() {
	return m_curScore.getHighestScore();
}


void Player::setStartTime() {
	double time  = ((double)(clock() - m_startTime) / CLOCKS_PER_SEC);
	if(time >= 1) {
		m_startTime = clock();
		moveRight();
	}
}


void Player::inchSnake() {
	// if(m_isSnakeMovingDown) {
	// 	moveDown();
		string xLoc_str = to_string(m_xLoc);
		char const *xLoc_char = xLoc_str.c_str();
		string yLoc_str = to_string(m_yLoc);
		char const *yLoc_char = yLoc_str.c_str();
		mvwaddstr(m_curwin, 10, 10, xLoc_char);
		mvwaddstr(m_curwin, 12, 12, yLoc_char);
	// }
	if(m_isSnakeMovingRight) {
		// moveRight();
	}
	if(m_isSnakeMovingLeft) {
		// moveLeft();
	}
	if(m_isSnakeMovingUp) {
		// moveUp();
	}
}


void Player::printChar(char playChar) {
	mvwaddch(m_curwin, 10, 10, playChar);
}

