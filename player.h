#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ncurses.h>
#include <curses.h>
#include <utility>
#include <vector>
#include <time.h>
#include <map>

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
	Score m_curScore;
  //// dont need a pointer
	//// want score to be tied to each instance of player
	//// but have 1 player at a time anyways
	pair<int, int> m_fruitPos;

	bool m_isSnakeMovingDown;
	bool m_isSnakeMovingRight;
	bool m_isSnakeMovingLeft;
	bool m_isSnakeMovingUp;

	bool m_isInit;
	clock_t m_startTime;

	public:
		Player();

		void initPlayer(WINDOW *win, int y, int x, char c);

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		int moveSnake();
		void displaySnake();	
		void storeCoords();
		void printSpace();

		bool getGameOverBoolean();
		void writeScore();
		void resetAllProperties();
		void setSnakeCharacter();

		void generateFruit();
		bool snakeHitFruit();
		int getFinalScore();

		void clearFruit();
		map<int, string> getHighScores();

		void printChar(char playChar);
		bool isInit();

		void setStartTime();
};

#endif
