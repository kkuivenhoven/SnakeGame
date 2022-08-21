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
	WINDOW * menuwin = newwin(6, xMax-12, yMax-8, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	// makes it so we can use arrow keys
	keypad(menuwin, true);

	string choices[3] = {"Walk", "Jog", "Run"};
	int choice;
	int highlight = 0;

	while(1) {
		for(int i = 0; i < 3; i++) {
			if(i == highlight) {
				wattron(menuwin, A_REVERSE); // A_REVERSE reverses foreground/BG color
			}
			mvwprintw(menuwin, i+1, 1, choices[i].c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch(choice) {
			case KEY_UP:
				highlight--;
				if(highlight == -1)  {
					highlight = 0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3)  {
					highlight = 2;
				}
				break;
			default:
				break;
		}

		if(choice == 10) {
			break; // break out of while loop bc means user hit enter	
		}
	}

	printw("Your choice was: %s", choices[highlight].c_str());

	// make sure program waist before exiting();
	getch();
	endwin();
	// nCurses

	return 0;
}

