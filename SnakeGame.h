#ifndef SNAKE_GAME
#define SNAKE_GAME

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <unistd.h> /* for sleep */
using namespace std;

class SnakeGame {
	int _height;
	int _width;
	int _gameover;
	int _score;
	int _flag;
	int _yCoordinateFruit;
	int _xCoordinateFruit;
	int _x;
	int _y;

	int _x_tutorial;
	int _y_tutorial;
	int _xBeg_tutorial;
	int _yBeg_tutorial;
	int _xMax_tutorial;
	int _yMax_tutorial;

	WINDOW *_win;

	public:
		SnakeGame();
		void draw();
		void setUpFruit();
		void input();

	private:
		int _kbhit();
		int _setUpFruit_xCoordinate();
		int _setUpFruit_yCoordinate();
};

#endif
