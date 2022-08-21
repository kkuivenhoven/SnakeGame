#ifndef _MENU_BAR_H_
#define _MENU_BAR_H_

#include <curses.h>
#include <string>
#include "menu.h"

using namespace std;

class MenuBar {
	WINDOW *m_win;
	Menu *m_menus;
	int m_num_menus;
	int m_selected_menu;
	bool m_isGameMode;

	public:
		MenuBar(WINDOW *win, Menu *menus, int num_menus);
		void draw();
		void handleTrigger(char trigger);
		bool getIsGameMode();
		void setMenuAtStart();
};

#endif
