#include "menubar.h"

MenuBar::MenuBar(WINDOW *win, Menu* menus, int num_menus) {
	this->m_win = win;
	this->m_menus = menus;
	this->m_num_menus = num_menus;
	this->m_selected_menu = -1;
	
	int current_pos = 2;
	for(int i = 0; i < m_num_menus; i++) {
		this->m_menus[i].setStartX(current_pos);
		string commandText = this->m_menus[i].getText();
		current_pos += (commandText.length() + 1);
		char triggerChar = this->m_menus[i].getTrigger();
		m_menuOptions.push_back(triggerChar);
	}
}


void MenuBar::clearMenu() {
	for(int i = 0; i < m_num_menus; i++) {
		int start_x = this->m_menus[i].getStartX();
		string text = this->m_menus[i].getText();
		mvwprintw(m_win, 0, start_x, text.c_str());
		wattroff(m_win, A_STANDOUT);
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
	if(trigger == 'o') {
		m_isGameMode = false;
		return;
	}
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


vector<char> MenuBar::getSetMenuOptions() {
	return m_menuOptions;
}


