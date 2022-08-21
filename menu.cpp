#include "menu.h"

Menu::Menu(string text, char trigger) {
	this->m_text = text;
	this->m_trigger = trigger;
}

void Menu::setStartX(int start_x) {
	m_start_x = start_x;	
}

int Menu::getStartX() {
	return m_start_x;
}

char Menu::getTrigger() {
	return m_trigger;
}

string Menu::getText() {
	return m_text;
}


