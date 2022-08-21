/* while (1) {
    // initialize variables with their default values here

    while ((c = wgetch)) {
        // Whatever input handling logic you need here

        if (gameOver)
            break;
    }

    // Any code that should run after the game over, 
		// like asking if the user wants to restart or 
		// quit and displaying thir final score 
		// and stuff like that I guess
} */


  while((ch = wgetch(win))) {
    if(isGameMode) {
      do { // while move is not equal to x  
        player->displaySnake();
        wrefresh(win); // show characters most recent location on screen
        playChar = player->moveSnake(); 
        isGameOver = player->getGameOverBoolean();
      } while((playChar != 'q') && (isGameOver != true));
      ch = playChar;  // handle character for when break out of do-while loop 
    }   
    if(isGameOver) { 
      mvwaddstr(win, (height/2), (width/2), "Gameover!");
      menuBar.clearMenu();
      player->resetAllProperties();
      wrefresh(win);
      sleep(3);
      mvwaddstr(win, (height/2), (width/2), "         ");
      isGameOver = false;
      isGameMode = false;
      ch = 'o';
      playChar = 'o';
    }   
    vector<char> menuOptions = menuBar.getSetMenuOptions();
    if(find(menuOptions.begin(), menuOptions.end(), ch) != menuOptions.end()) {
      menuBar.handleTrigger(ch);
      menuBar.draw();
      if(ch == 'q') { break; }
      if(ch == 's') {
        isGameMode = true;
        if(player == nullptr) {
          player = new Player(win, 1, 1, '@');
        } else {
          player->setSnakeCharacter();
          player->displaySnake();
        }   
      }   
    }   
  }
