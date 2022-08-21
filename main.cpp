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
#include <math.h>
#include <map>
#include <time.h>
#include <stdlib.h>

#include "player.h"
#include "menubar.h"
using namespace std;

// https://linux.die.net/man/3/border
// https://pubs.opengroup.org/onlinepubs/7908799/xcurses/box.html
// https://linux.die.net/man/3/clear

int main() {
	initscr();
	noecho();
	curs_set(0);

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	int yMax_80 = ceil(((yMax*80)/100));
	int xMax_80 = ceil(((xMax*80)/100));

	int yPos = ((yMax - yMax_80)/2);
	int xPos = ((xMax - xMax_80)/2);

	WINDOW *win = newwin(yMax_80, xMax_80, yPos, xPos);
	box(win, 0, 0);
	keypad(win, true);
	
	int nLines = yMax_80;
	int nCols = xMax_80;
	int beginY = yPos;
	int beginX = xPos;

	int height = (yMax_80 - yPos);
	int width = (xMax_80 - xPos);

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
		// if(player.isInit() != true) {
			player.initPlayer(win, 1, 1, '@');
		// }
		nodelay(win, true);

    while((ch = wgetch(win))) {
				menuBar.handleTrigger(ch);
				menuBar.draw();
				if(ch == 'q') { break; }
				if(ch == 's') { 
					isGameMode = true; 
					player.generateFruit();
				}

				/* player.displaySnake();
				player.generateFruit();
				playChar = player.moveSnake();
				player.inchSnake();
				wrefresh(win); */
				if(isGameMode) {
					do { 
					// while(1) {
						player.displaySnake();
						wrefresh(win);
						playChar = player.moveSnake();
						isGameOver = player.getGameOverBoolean();

						// if((playChar != KEY_UP) && (playChar != KEY_DOWN) 
							// && (playChar != KEY_LEFT) && (playChar != KEY_RIGHT)) {
						// player.inchSnake();
							// player.generateFruit();
						// }
						
						// player.generateFruit();
						if(player.snakeHitFruit()) {
							player.generateFruit();
						}
						if((playChar != 'q') && (isGameOver != true)) {
							break;
						}
					} while((playChar != 'q') && (isGameOver != true));
					// player.generateFruit();
					ch = playChar;
				}
					
        if(isGameOver) { break; }
				if(playChar == 'q') { break; } 
    } 

		if(isGameOver) {
			player.clearFruit();
			player.writeScore();

			int finalScore = player.getFinalScore();
			string finalScore_str = to_string(finalScore);
			char const *finalScore_char = finalScore_str.c_str();

			int subWin_yMax; 
			int subWin_xMax; 
			int subWin_yBegin; 
			int subWin_xBegin; 

			getbegyx(win, subWin_yBegin, subWin_xBegin);
			getmaxyx(win, subWin_yMax, subWin_xMax);

			WINDOW *gameOverWin = subwin(stdscr, ((height * 20)/100), width, yPos + 1, xPos + 4);
			box(gameOverWin, 0, 0);
			int gameOver_yMax; 
			int gameOver_xMax; 
			getmaxyx(gameOverWin, gameOver_yMax, gameOver_xMax);
			char myWord[10];
			strcpy(myWord, "Game over!");
			mvwaddstr(gameOverWin, (gameOver_yMax/2), (gameOver_xMax/2)-5, myWord); 
			touchwin(gameOverWin);
			wrefresh(gameOverWin); 
	
			WINDOW *playerScoreWin = subwin(stdscr, ((height * 20)/100), width, 
																	yPos + gameOver_yMax + 1, xPos + 4);
			box(playerScoreWin, 0, 0);
			int playerScoreWin_yMax; 
			int playerScoreWin_xMax; 
			getmaxyx(playerScoreWin, playerScoreWin_yMax, playerScoreWin_xMax);
			char scoreCard[14];
			strcpy(scoreCard, "Your score: ");
			strcat(scoreCard, finalScore_char);
			mvwaddstr(playerScoreWin, (playerScoreWin_yMax/2), (playerScoreWin_xMax/2)-7, scoreCard); 
			touchwin(playerScoreWin);
			wrefresh(playerScoreWin);  

			WINDOW *highScoreWin = subwin(stdscr, ((height * 60)/100), width, 
																			yPos + gameOver_yMax + playerScoreWin_yMax+ 1, xPos + 4);
			box(highScoreWin, 0, 0);
			int highScoreWin_yMax; 
			int highScoreWin_xMax; 
			getmaxyx(highScoreWin, highScoreWin_yMax, highScoreWin_xMax);
			char highScoreCard[12];
			strcpy(highScoreCard, "High scores:");
			mvwaddstr(highScoreWin, 1, (highScoreWin_xMax/2)-6, highScoreCard); 

			map<int, string> highScores = player.getHighScores();
			int i = 0;
			for(auto itr = highScores.rbegin(); itr != highScores.rend(); ++itr) {
				int scoreToDisplay = itr->first;
				string scoreToDisplay_str = to_string(scoreToDisplay);
				char const *scoreToDisplay_char = scoreToDisplay_str.c_str();

				string dateOfScore = itr->second;
				
				mvwaddstr(highScoreWin, (i + 2), (highScoreWin_xMax/2) - 7, scoreToDisplay_char);
				mvwaddstr(highScoreWin, (i + 2), (highScoreWin_xMax/2) - 4, itr->second.c_str());
				i+=1;
				if((highScoreWin_yMax-1) == (i+2)) {
					break;
				}
			}

			touchwin(highScoreWin);
			wrefresh(highScoreWin);  

			menuBar.clearMenu();
			player.resetAllProperties();

			sleep(3);

			werase(gameOverWin);
			wrefresh(gameOverWin);

			werase(playerScoreWin);
			wrefresh(playerScoreWin);

			werase(highScoreWin);
			wrefresh(highScoreWin);

			wrefresh(win);

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

	mvwprintw(win, (height/2)-1, (width/2), "Quitting game...");
	
	wrefresh(win);
	sleep(3);

	endwin();
	delwin(win);

	return 0;
}
