#include "menubar.h"

MenuBar::MenuBar(WINDOW *win, Menu* menus, int num_menus) {
	this->m_win = win;
	this->m_menus = menus;
	this->m_num_menus = num_menus;
	this->m_selected_menu = -1;
	
	int current_pos = 2;
	for(int i = 0; i < m_num_menus; i++) {
		this->m_menus[i].setStartX(current_pos);
		current_pos += this->m_menus[i].getText().length() + 1;
	}
}


void MenuBar::draw() {
	for(int i = 0; i < m_num_menus; i++) {
		int start_x = this->m_menus[i].getStartX();
		string text = this->m_menus[i].getText();
		if(m_selected_menu == i) {
			wattron(m_win, A_STANDOUT);
		}
		mvwprintw(m_win, 0, start_x, text.c_str());
		wattroff(m_win, A_STANDOUT);
	}
}


void MenuBar::handleTrigger(char trigger) {
	for(int i = 0; i < m_num_menus; i++) {
		if(trigger == this->m_menus[i].getTrigger()) {
			m_selected_menu = i;
			if(trigger == 's') {
				m_isGameMode = true;
			}
			if(trigger == 'q') {
				m_isGameMode = false;
			}
		}
	}
}

/* void MenuBar::setMenuAtStart() {
	int start_x = this->m_menus[0].getStartX();
	string text = this->m_menus[0].getText();
	wattron(m_win, A_STANDOUT);
	mvwprintw(m_win, 0, start_x, text.c_str());
} */

bool MenuBar::getIsGameMode() {
	return m_isGameMode;
}

