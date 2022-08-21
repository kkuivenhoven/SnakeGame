#include "player.h"

Player::Player(WINDOW *win, int y, int x, char c) {
	curwin = win;
	yLoc = y;
	xLoc = x;
	getmaxyx(curwin, yMax, xMax);
	keypad(curwin, true);
	character = c;
}

void Player::mvup() {
	mvwaddch(curwin, yLoc, xLoc, '.');
	// coordinate system moves from top down
	yLoc--;
	if(yLoc < 1) { // out of bounds 
		yLoc = 1;
	}
}

void Player::mvdown() {
	mvwaddch(curwin, yLoc, xLoc, '.');
	yLoc++;
	if(yLoc > yMax-2) { // first theres the border (yMax - 1), then 1 in from border
		yLoc = yMax - 2;
	}
}

void Player::mvleft() {
	mvwaddch(curwin, yLoc, xLoc, '.');
	xLoc--;
	if(xLoc < 1) {
		xLoc = 1;
	}
}

void Player::mvright() {
	mvwaddch(curwin, yLoc, xLoc, '.');
	xLoc++;
	if(xLoc > xMax - 2) {
		xLoc = xMax - 2;
	}
}


int Player::getmv() {
	int choice = wgetch(curwin);
	switch(choice) {
		case KEY_UP:
			mvup();
			break;
		case KEY_DOWN:
			mvdown();
			break;
		case KEY_LEFT:
			mvleft();
			break;
		case KEY_RIGHT:
			mvright();
			break;	
		default:
			break;
	}
	return choice;
}

void Player::display() {
	mvwaddch(curwin, yLoc, xLoc, character);
}
