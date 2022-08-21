#include <ncurses.h>
#include <string>
using namespace std;
void start_ncurses(bool useRaw, bool useNoEcho);
void printMenu(WINDOW *menu, string choices[], int size, int hightlight);

int main(int argc, char **argv){
	// nCurses Start
	initscr();
	noecho();
	cbreak();	

	int y, x, yBeg, xBeg, yMax, xMax;

	WINDOW *win = newwin(10, 20, 10, 10);

	getyx(stdscr, y, x);
	getbegyx(stdscr, yBeg, xBeg);
	getmaxyx(stdscr, yMax, xMax);

	// printw(" %d %d %d %d %d %d", y, x, yBeg, xBeg, yMax, xMax);

	mvprintw(yMax/2, xMax/2, "hello");
	mvprintw((yMax/2) - 10, (xMax/2)-10, "%d %d", yBeg, xBeg);

	// make sure program waits before exiting...
	getch();
	endwin();
	// nCurses end

	return 0;
}
