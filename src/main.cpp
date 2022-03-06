#include <iostream>
#include <ncurses.h>

int main(int argc, char** argv) {
	initscr();
	printw("Welcome to Terade!");
	refresh();
	getch();
	endwin();

	return 0;
}
