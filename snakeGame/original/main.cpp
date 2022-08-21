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

#include "player.h"
#include "menubar.h"
using namespace std;

// https://linux.die.net/man/3/border
// https://pubs.opengroup.org/onlinepubs/7908799/xcurses/box.html

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

			player.writeScore();

			// newwin(int nlines, int ncols, int begin_y, int begin_x)
			WINDOW *myWin = newwin(nLines/2, nCols/2, (yMax/4) + (nLines/4), (xMax/4) + (width/2)-1);
			int myWinHeight = (nLines/2);
			int myWinCols = (nCols/2);
			int begin_y = ((yMax/4) + (nLines/4));
			int begin_x = ((xMax/4) + (width/2)-1);
			box(myWin, 0, 0);
			touchwin(myWin);
			wrefresh(myWin);

			char myWord[14];
			strcpy(myWord, "Game over! ");
			mvwaddstr(myWin, ((myWinHeight/2)-1), (myWinCols/4)+1, myWord); // good

			char scoreCard[10];
			strcpy(scoreCard, "Score: ");
			strcat(scoreCard, finalScore_char);

			// mvwaddstr(window *win, int y, int x, const char *str);
			mvwaddstr(myWin, (myWinHeight/2), (myWinCols/4)+2, scoreCard); // good

			// mvwaddstr(myWin, (myWinHeight+1), (myWinCols-1), "kkkk"); 
			// mvwaddstr(myWin, (myWinHeight/4), (myWinCols-1), "oooo"); 
			// mvwaddstr(myWin, (myWinHeight/4)+1, (myWinCols-1), "oooo"); 

			mvwaddstr(win, begin_y+3, begin_x+3, "----"); 
			mvwaddstr(myWin, (myWinHeight/2)+1, (myWinCols-1), "oooo"); 
			mvwaddstr(myWin, (myWinHeight/2), (myWinCols-1), "pppp"); 
			mvwaddstr(myWin, (myWinHeight/2)-1, (myWinCols-1), "eeee"); 

			// mvwaddstr(myWin, (myWinHeight)+1, (myWinCols-1), "oooo"); 
			// mvwaddstr(myWin, (myWinHeight), (myWinCols-1), "pppp"); 
			// mvwaddstr(myWin, (myWinHeight)-1, (myWinCols-1), "pppp"); 

			wrefresh(myWin);

			menuBar.clearMenu();
			player.resetAllProperties();
			wrefresh(win);
			sleep(5);
			// mvwaddstr(win, (height/2), (width/2), "                ");
			// mvwaddstr(win, (height/2)+1, (width/2), "              ");
			mvwaddstr(myWin, ((myWinHeight/2)-1), (myWinCols/4)+1, "           ");
			mvwaddstr(myWin, (myWinHeight/2), (myWinCols/4)+2, "           ");
			mvwaddch(myWin, (yMax/4) + (nLines/4), (xMax/4) + (width/2)-1, ' ');
			isGameOver = false;
			isGameMode = false;
      // https://docs.oracle.com/cd/E19455-01/816-3323/6m9k40u1l/index.html
			// border_set(myWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
			// border_set(myWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
			// box(myWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
			box(myWin, ' ', ' ');
			// mvwaddch(myWin, (myWinHeight/2), (myWinCols/2), 'o'); 
			// wborder(myWin, ' ', ' ', ' ', ' ', 0, 0, 0, 0);
			touchwin(myWin);
			wrefresh(myWin);
			delwin(myWin);
		}

    // Any code that should run after the game over, 
		// like asking if the user wants to restart or quit 
		// and displaying thir final score 
		if((playChar == 'q') || (ch == 'q')){ 
			menuBar.handleTrigger(playChar);
			break; 
		}
	} 

	mvwprintw(win, (height/2)-1, (width/2), "Quitting game...");
	
	wrefresh(win);
	sleep(3);

	endwin();
	delwin(win);

	return 0;
}
