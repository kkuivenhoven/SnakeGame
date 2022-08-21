#include <iostream>
#include <ncurses.h>
#include <curses.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <time.h>
#include <cstddef>
#include <form.h>
#include <ncurses/curses.h>

#include "player.h"
#include "menubar.h"
using namespace std;

int main() {
	initscr();
	noecho();
	curs_set(0);

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *win = newwin(yMax/2, xMax/2, yMax/4, xMax/4);
	box(win, 0, 0);
	keypad(win, true);
	
	int nLines = (yMax/2);
	int nCols = (xMax/2);
	int beginY = (yMax/4);
	int beginX = (xMax/4);

	int height = ((yMax/2) - (yMax/4));
	int width = ((xMax/2) - (xMax/4));

	Menu menus[2] = {
		Menu("Start[s]", 's'),
		Menu("Quit[q]", 'q')
	};

	MenuBar menuBar = MenuBar(win, menus, 2);
	menuBar.draw();

	bool isGameMode = false;
	bool isGameOver = false;
	char ch;
	char playChar;
	while (1) {
		Player player;
		player.initPlayer(win, 1, 1, '@');

    while((ch = wgetch(win))) {
				menuBar.handleTrigger(ch);
				menuBar.draw();
				if(ch == 'q') { break; }
				if(ch == 's') { 
					isGameMode = true; 
					player.generateFruit();
				}

				if(isGameMode) {
					do { 
						player.displaySnake();
						wrefresh(win);
						playChar = player.moveSnake();
						isGameOver = player.getGameOverBoolean();
						if(player.snakeHitFruit()) {
							player.generateFruit();
						}
					} while((playChar != 'q') && (isGameOver != true));
					ch = playChar;
				}
					
        if(isGameOver) { break; }
				if(playChar == 'q') { break; }
    }

		if(isGameOver) {
			player.clearFruit();

			int finalScore = player.getFinalScore();
			string finalScore_str = to_string(finalScore);
			char const *finalScore_char = finalScore_str.c_str();

			// char myWord[14];
			// strcpy(myWord, "Game over! ");
			// mvwaddstr(win, (height/2), (width/2), myWord);

			// char scoreCard[10];
			// strcpy(scoreCard, "Score: ");
			// strcat(scoreCard, finalScore_char);
			// mvwaddstr(win, ((height/2)+1), (width/2), scoreCard);

			player.writeScore();

			// WINDOW *myWin = newwin(5,5,1,1);
			// WINDOW *myWin = newwin(5,5,1,1);
			// WINDOW *myWin = newwin(beginY,beginX,1,1);
			// WINDOW *myWin = newwin(5, 5, (beginY + (height/2) + 5), (beginX + (width/2)));
			// WINDOW *myWin = newwin(10, 10, ((height/2) - 1), (beginX + (width/2)));
			// WINDOW *myWin = newwin(5, 15, (yMax/4)+3, (xMax/4) + (width/2)-1);
			// WINDOW *myWin = newwin(7, 15, (yMax/4)+3, (xMax/4) + (width/2)-1);
			//                    nLines, nCols, beginY, beginX
			// WINDOW *myWin = newwin(7, 15, (yMax/4) + (nLines/4), (xMax/4) + (width/2)-1);
			WINDOW *myWin = newwin(nLines/2, nCols/2, (yMax/4) + (nLines/4), (xMax/4) + (width/2)-1);
			// int myWinHeight = 7;
			int myWinHeight = (nLines/2);
			// int myWinCols = 15;
			int myWinCols = (nCols/2);
			// wattron(myWin, COLOR_BLUE);
			box(myWin, 0, 0);
			touchwin(myWin);
			wrefresh(myWin);
			// wattroff(myWin, COLOR_BLUE);

			char myWord[14];
			strcpy(myWord, "Game over! ");
			// docs: int mvwaddstr(WINDOW *win, int y, int x, const char *str);
			// mvwaddstr(myWin, (myWinHeight/2), (myWinCols/2), myWord);
			mvwaddstr(myWin, ((myWinHeight/2)-1), (myWinCols/4)+1, myWord); // good
			// mvwaddstr(myWin, ((yMax/4) + (nLines/4)), ((xMax/4) + (width/2) - 1), myWord);

			char scoreCard[10];
			strcpy(scoreCard, "Score: ");
			strcat(scoreCard, finalScore_char);
			mvwaddstr(myWin, (myWinHeight/2), (myWinCols/4)+2, scoreCard); // good
			// good: mvwaddstr(myWin, ((myWinHeight/2)+1), (myWinCols/4)+2, scoreCard);
			// mvwaddstr(myWin, ((myWinHeight/2)+1), (myWinCols/2), scoreCard);

			wrefresh(myWin);
			/* int y1 = (yMax/8);
			int y2 = (y1 + 5);
			int x1 = (xMax/8);
			int x2 = (x1 + 5);

			mvhline(y1, x1, 0, x2-x1);
			mvhline(y2, x1, 0, x2-x1);
			mvvline(y1, x1, 0, y2-y1);
			mvvline(y1, x2, 0, y2-y1);
			mvaddch(y1, x1, ACS_ULCORNER);
			mvaddch(y2, x1, ACS_LLCORNER);
			mvaddch(y1, x2, ACS_URCORNER);
			mvaddch(y2, x2, ACS_LRCORNER); */

			// WINDOW *highScoreMenu = subwin(yMax/4, xMax/4, (yMax/4) + 5, (xMax/4) + 5);
			/* WINDOW *subWindow = subwin(win,2,0,20,30);
			box(subWindow, 0, 0);
			keypad(subWindow, true); */

			/* WINDOW *subWindow = newwin(yMax/4, xMax/4, (yMax/4) + 5, (xMax/4) + 5);
			refresh();
			box(subWindow,0,0);
			mvwprintw(subWindow,1,1,"SubWindow");
			refresh();
			wrefresh(subWindow); */

			menuBar.clearMenu();
			player.resetAllProperties();
			wrefresh(win);
			sleep(3);
			mvwaddstr(win, (height/2), (width/2), "           ");
			mvwaddstr(win, (height/2)+1, (width/2), "           ");
			isGameOver = false;
			isGameMode = false;
		}

    // Any code that should run after the game over, 
		// like asking if the user wants to restart or quit 
		// and displaying thir final score 
		if((playChar == 'q') || (ch == 'q')){ 
			menuBar.handleTrigger(playChar);
			break; 
		}
	} 

	mvwprintw(win, (height/2), (width/2), "Quitting game...");
	
	wrefresh(win);
	sleep(3);

	endwin();
	delwin(win);

	return 0;
}
