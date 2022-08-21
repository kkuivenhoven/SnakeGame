#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <curses.h>
#include "menu.h"

using namespace std;

int main(int argc, char **argv) {
	initscr();
	noecho();
	curs_set(0);

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	WINDOW *win = newwin(yMax/2, xMax/2, yMax/4, xMax/4);
	box(win, 0, 0);

	Menu menus[3] = {
		Menu("File", 'f'),
		Menu("Edit", 'e'),
		Menu("Options", 'o')
	};

	MenuBar menubar = MenuBar(win, menus, 3);
	menubar.draw();

	char ch;
	while((ch = wgetch(win))) {
		menubar.handleTrigger(ch);
		menubar.draw();
	}

	endwin();
	return 0;
}
