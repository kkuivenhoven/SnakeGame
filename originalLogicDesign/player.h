#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ncurses.h>
#include <curses.h>
#include <utility>
#include <vector>

#include "score.h"

using namespace std;

class Player {
	bool m_gameover;
	int m_xLoc;
	int m_yLoc;
	int m_xMax;
	int m_yMax;
	char m_character;
	WINDOW *m_curwin;
	vector<pair<int, int> > snakeCoords;
	pair<int, int> formerSnakePrint;
	Score *m_curScore;
  //// dont need a pointer
	//// want score to be tied to each instance of player
	//// but have 1 player at a time anyways

	public:
		Player(WINDOW *win, int y, int x, char c);
		~Player();

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		int moveSnake();
		void displaySnake();	
		void storeCoords();
		void printSpace();

		bool getGameOverBoolean();
		void resetAllProperties();
		void setSnakeCharacter();
};

#endif
