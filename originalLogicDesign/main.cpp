#include <iostream>
#include <ncurses.h>
#include <curses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <time.h>
#include <cstddef>

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

	int height = ((yMax/2) - (yMax/4));
	int width = ((xMax/2) - (xMax/4));

	Menu menus[2] = {
		Menu("Start[s]", 's'),
		Menu("Quit[q]", 'q')
	};

	MenuBar menuBar = MenuBar(win, menus, 2);
	menuBar.draw();

	Player *player = nullptr;

	bool isGameMode = false;
	bool isGameOver = false;
	char ch;
	char playChar;
/* while (1) {
    // initialize variables with their default values here

    while ((c = wgetch)) {
        // Whatever input handling logic you need here

        if (gameOver)
            break;
    }

    // Any code that should run after the game over, like asking if the user wants to restart or quit and displaying thir final score and stuff like that I guess
} */
	while((ch = wgetch(win))) {
		if(isGameMode) {
			do { /* while move is not equal to x  */
				player->displaySnake();
				wrefresh(win); /* show characters most recent location on screen */
				playChar = player->moveSnake();	
				isGameOver = player->getGameOverBoolean();
			} while((playChar != 'q') && (isGameOver != true));
			ch = playChar;  /* handle character for when break out of do-while loop */
		}
		if(isGameOver) { 
			mvwaddstr(win, (height/2), (width/2), "Gameover!");
			menuBar.clearMenu();
			player->resetAllProperties();
			wrefresh(win);
			sleep(3);
			mvwaddstr(win, (height/2), (width/2), "         ");
			isGameOver = false;
			isGameMode = false;
			ch = 'o';
			playChar = 'o';
		}
		vector<char> menuOptions = menuBar.getSetMenuOptions();
		if(find(menuOptions.begin(), menuOptions.end(), ch) != menuOptions.end()) {
			menuBar.handleTrigger(ch);
			menuBar.draw();
			if(ch == 'q') { break; }
			if(ch == 's') {
				isGameMode = true;
				if(player == nullptr) {
					player = new Player(win, 1, 1, '@');
				} else {
					player->setSnakeCharacter();
					player->displaySnake();
				}
			}
		}
	}

	mvwprintw(win, (height/2), (width/2), "Quitting game...");
	
	wrefresh(win);
	sleep(3);

	endwin();
	delwin(win);

	return 0;
}
