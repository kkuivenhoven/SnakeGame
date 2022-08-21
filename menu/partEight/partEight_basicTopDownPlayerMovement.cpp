#include <ncurses.h>
#include <curses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.h"
using namespace std;
void start_ncurses(bool useRaw, bool useNoEcho);
void printMenu(WINDOW *menu, string choices[], int size, int hightlight);

int main(int argc, char **argv){
	// nCurses Start
	initscr();
	noecho();
	cbreak();	

	// get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// create a window for our input
	WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
	box(playwin, 0, 0);
	refresh();
	wrefresh(playwin);

	Player *p = new Player(playwin, 1, 1, '@');
	
	// need to print before we get the choice and so character shows up
	// immediately when we start the program
	do { // while move is not equal to x
		p->display();
		wrefresh(playwin); // show characters most recent location on screen
  } while(p->getmv() != 'x'); // while move is not equal to x
 

	// make sure program waist before exiting();
	endwin();
	// nCurses

	return 0;
}


