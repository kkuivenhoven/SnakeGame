#include "player.h"

Player::Player(WINDOW *win, int y, int x, char c) {
	m_curwin = win;
	m_yLoc = y;
	m_xLoc = x;
	getmaxyx(m_curwin, m_yMax, m_xMax);
	m_character = c;
	m_gameover = false;
}

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


void Player::printSpace() {
	storeCoords();
	mvwaddch(m_curwin, formerSnakePrint.first, formerSnakePrint.second, ' ');
}


void Player::moveUp() {
	// printSpace();
	// coordinate system moves from top down
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_yLoc--;
	if(m_yLoc < 1) { 
		m_gameover = true;	
		// m_yLoc = 1;
	} 
}


void Player::moveDown() {
	// printSpace();
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_yLoc++;
	if(m_yLoc > m_yMax-2) { 
		m_gameover = true;	
		// m_yLoc = m_yMax - 2;
	} 
}


void Player::moveLeft() {
	// printSpace();
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_xLoc--;
	if(m_xLoc < 1) {
		m_gameover = true;	
		// m_xLoc = 1;
	} 
}


void Player::moveRight() {
	// printSpace();
	mvwaddch(m_curwin, m_yLoc, m_xLoc, ' ');
	m_xLoc++;
	if(m_xLoc > m_xMax - 2) {
		m_gameover = true;	
		// m_xLoc = m_xMax - 2;
	} 
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
		for(std::vector<pair<int, int> >::iterator it = snakeCoords.begin(); it != snakeCoords.end(); it++) {
			mvwaddch(m_curwin, it->first, it->second, m_character);
		}
	} else {
		mvwaddch(m_curwin, m_yLoc, m_xLoc, m_character);
	} */
}



