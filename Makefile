all: main.o player.o player.h menubar.o menubar.h menu.o menu.h score.o score.h
	/usr/bin/g++ -o SnakeGame main.o player.o menubar.o menu.o score.o -lncurses

clean:
	rm -rf *.o
	rm -rf SnakeGame
