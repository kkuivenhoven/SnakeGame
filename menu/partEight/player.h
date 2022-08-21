#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ncurses.h>
#include <curses.h>

class Player {
	public:
		Player(WINDOW *win, int y, int x, char c);

		void mvup();
		void mvdown();
		void mvleft();
		void mvright();
		int getmv();	
		void display();

	private:
		int xLoc, yLoc, xMax, yMax;
		char character;
		WINDOW *curwin;
};

#endif
