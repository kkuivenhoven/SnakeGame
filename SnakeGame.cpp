#include "SnakeGame.h"

SnakeGame::SnakeGame() { 
	_height = 30;
	_width = 30;
	_gameover = 0;
	_score = 0;
	_flag = 0;
	_x = (_height/2);
	_y = (_width/2);

	initscr();
	cbreak();
	noecho(); 

	// also helpful: https://www.youtube.com/watch?v=GYuJ_Dcupfk
	getyx(stdscr, _y_tutorial, _x_tutorial);
	getbegyx(stdscr, _yBeg_tutorial, _xBeg_tutorial);
	getmaxyx(stdscr, _yMax_tutorial, _xMax_tutorial);

	_height = _yMax_tutorial;
	_width = _xMax_tutorial;

	_win = newwin(10, 20, 10, 10);

	// below is helpful for making windows
	mvprintw(_yMax_tutorial/2, _xMax_tutorial/2, "hello");
}


void SnakeGame::draw() {
	// system("cls");
	for(int i = 0; i < _height; i++) {
		for(int j = 0; j < _width; j++) {
			if(i == 0) { // ceiling
				printf("*");
			}
			else if((_width - 1) == i) { // floor
				printf("*");
			}
			else if(j == 0) { // left wall
				printf("*");
			}
			else if(j == (_height - 1)) { // right wall
				printf("*");
			}
			else {
				printf(" ");
			} 
		}
		printf("\n");
	}
}


int SnakeGame::_kbhit() {
	int ch = getch();
	if(ch != ERR) {
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}


void SnakeGame::input() {
	/* initscr();
	cbreak();
	noecho(); */

	keypad(stdscr, TRUE);
	if(_kbhit()) {
		switch(getch()) {
			case KEY_LEFT:
				// printf(" case key left\n");
				mvwprintw(stdscr, 1, 1, "You pressed < key!");
				wrefresh(stdscr);
				_flag = 1;
				break;
			case KEY_DOWN:
				// cout << " case key down\n";
				mvwprintw(stdscr, 2, 1, "You pressed down key!");
				wrefresh(stdscr);
				_flag = 2;
				break;
			case KEY_RIGHT:
				// cout << " case key right\n";
				mvwprintw(stdscr, 3, 1, "You pressed > key!");
				wrefresh(stdscr);
				_flag = 3;
				break;
			case KEY_UP:
				// cout << " case key up\n";
				mvwprintw(stdscr, 4, 1, "You pressed ^ key!");
				wrefresh(stdscr);
				_flag = 4;
				break;
			case 'q':
				// cout << " case q\n";
				_gameover = 1;
				endwin();
				break;
		}
	}
}
				

int SnakeGame::_setUpFruit_xCoordinate() {
	srand(time(0));
	int _xCoordinateFruit = (rand()%30);
	if(_xCoordinateFruit == 0) { 
		_setUpFruit_xCoordinate();
	} else {
		return _xCoordinateFruit;
	}
}


int SnakeGame::_setUpFruit_yCoordinate() {
	srand(time(0));
	_yCoordinateFruit = (rand()%30);
	if(_yCoordinateFruit == 0) {
		_setUpFruit_yCoordinate();
	} else {
		return _yCoordinateFruit;
	}
}



