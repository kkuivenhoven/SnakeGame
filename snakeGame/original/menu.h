#ifndef _MENU_H_
#define _MENU_H_

#include <curses.h>
#include <string>

using namespace std;

class Menu {
	int m_start_x; // i.e. menu starts at position 2
	string m_text;
	char m_trigger;

	public:
		Menu(string text, char trigger);

		void setStartX(int start_x);

		int getStartX();
		char getTrigger();
		string getText();
};

#endif
