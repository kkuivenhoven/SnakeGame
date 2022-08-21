#include <iostream>
#include <stdio.h>
#include <string>
#include "SnakeGame.h"
using namespace std;

void startGame() {
	SnakeGame snakeGame;
	printf("------ Starting the game! ------\n");
	snakeGame.draw();
	//while(1) {
	snakeGame.input();
	//}
	printf(" ------ after input() call ========\n");
}

int main() {
	char userInput = 'P';
	bool start = true;

	while(1) {
		if(start) {
			cout << "*******************************************\n" <<
				"-- Press the following keys to continue: --\n" <<
				"--              S - start                --\n" <<
				"--              Q - quit                 --\n" <<
				"*******************************************\n";
			start = false;
		}
		userInput = cin.get();
		cin.ignore();
		if(userInput == 'Q') {
			break;
		}
		else if(userInput == 'S') {
			// startGame();
			break;
		}
		else {
			cout << "You have entered an invalid key.\nPlease try again.\n";
		}
	}

	if(userInput == 'S') {
		SnakeGame snakeGame;
		printf("------ Starting the game! ------\n");
		snakeGame.draw();
		while(1) {
			snakeGame.input();
		}
	}

	cout << "Quitting game!\n";

	return 0;
}
