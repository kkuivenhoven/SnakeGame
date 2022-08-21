#include <ncurses.h>
#include <curses.h>
#include <string>
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
	WINDOW * inputwin = newwin(3, xMax-12, yMax-5, 5);
	box(inputwin, 0, 0);
	refresh();
	wrefresh(inputwin);

	keypad(inputwin, true);

	int c = wgetch(inputwin);
	if(c == KEY_UP) {
		mvwprintw(inputwin, 1, 1, "You pressed up!");
		wrefresh(inputwin);
	}
	
	// make sure program waist before exiting();
	getch();
	endwin();
	// nCurses

	return 0;
}

