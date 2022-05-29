#include "view_curses.h"

void view_curses::setup() {
	initscr();
	nodelay(stdscr, false);
	keypad(stdscr, true);
	//noecho();
	curs_set(0);
	start_color();
	refresh();

	for (int i = 0; i < 75; i++) {
		clear_line_[i] = ' ';
	}

	setup_prompt();
	setup_main_list();
	setup_status_bar();
	setup_colors();
}

void view_curses::setup_prompt() {
	prompt_ = newwin(prompt_ht, prompt_wd, 0, 0);
	box(prompt_, 0, 0);
	mvwprintw(prompt_, 0, 2, "Terade");
	mvwprintw(prompt_, 1, 1, "Welcome to Terade! Type 'help' for more info.");
	mvwprintw(prompt_, 3, 1, ">");
	wrefresh(prompt_);
}

void view_curses::setup_main_list() {
	main_list_ = newwin(list_ht, list_wd, prompt_ht, 0);
	set_list_title("");
}

void view_curses::setup_status_bar() {
	status_bar_ = newwin(status_ht, status_wd, maxheight_, 0);
	mvwprintw(status_bar_, 0, 1, "Status Bar");
	wrefresh(status_bar_);
}

void view_curses::update_list(const std::vector<std::string>& items, const std::string& header) {
	clear_list();
	mvwprintw(main_list_, 2, 2, header.c_str());
	std::string divider(list_wd-4, '-');
	mvwprintw(main_list_, 3, 2, divider.c_str());
	int line_number = 4;
	for (const auto& item: items) {
		mvwprintw(main_list_, line_number, 2, item.c_str());
		line_number += 2;
	}
	wrefresh(main_list_);
}

void view_curses::set_list_title(const std::string& title) {
	box(main_list_, 0, 0);
	mvwprintw(main_list_, 0, 2, title.c_str());
	wrefresh(main_list_);
}

void view_curses::clear_list() {
	for (int line_num = 1; line_num < list_ht - 1; line_num++) {
		mvwprintw(main_list_, line_num, 1, clear_line_);
	}
}

void view_curses::update_status_bar(const player& p) {
	mvwprintw(status_bar_, 0, 0, clear_line_);
	mvwprintw(status_bar_, 0, 1, (p.name() + " (Cash: $" + prettify_price(p.available_cash()) + ")").c_str());
	wrefresh(status_bar_);
}

std::string view_curses::get_entry() {
	char str[100];
	mvwprintw(prompt_, 3, 1, clear_line_);
	mvwprintw(prompt_, 3, 1, "> ");
	wrefresh(prompt_);
	wgetstr(prompt_, str);
	return std::string(str);
}

std::string view_curses::get_input(const std::string& prompt) {
	std::string input;
	while (input == "") {
		input = get_input_curses(prompt);
	}
	return input;
}

std::string view_curses::get_input_curses(const std::string& prompt) {
	char input[20];
	input_win = newwin(input_ht, input_wd, (maxheight_ - input_ht) / 2, (maxwidth_ - input_wd) / 2);
	wbkgd(input_win, COLOR_PAIR(1));
	wattron(input_win, COLOR_PAIR(1));
	box(input_win, 0, 0);
	mvwprintw(input_win, 0, 2, "Input");
	mvwprintw(input_win, 1, 1, (prompt + ": ").c_str());
	wrefresh(input_win);
	wgetstr(input_win, input);
	wattroff(input_win, COLOR_PAIR(1));


	delwin(input_win);
	touchwin(prompt_);
	wrefresh(prompt_);
	touchwin(main_list_);
	wrefresh(main_list_);
	
	return std::string(input);
}

void view_curses::show_error(const std::string& error_msg) {
	wattron(status_bar_, COLOR_PAIR(2));
	mvwprintw(status_bar_, 0, 0, clear_line_);
	mvwprintw(status_bar_, 0, 1, ("Error: " + error_msg).c_str());
	wrefresh(status_bar_);
	wattroff(status_bar_, COLOR_PAIR(2));
}

void view_curses::show_help() {
	help_win_ = newwin(help_ht, help_wd, (maxheight_ - help_ht) / 2, (maxwidth_ - help_wd) / 2);	
	wbkgd(help_win_, COLOR_PAIR(1));
	wattron(help_win_, COLOR_PAIR(1));
	box(help_win_, 0, 0);
	mvwprintw(help_win_, 0, 2, "Commands Available");
	mvwprintw(help_win_, 1, 1, "* buy          Purchase an asset");
	mvwprintw(help_win_, 2, 1, "* sell         Sell an asset");
	mvwprintw(help_win_, 3, 1, "* assets       Show list of assets");
	mvwprintw(help_win_, 4, 1, "* portfolio    Show the selected portfolio");
	mvwprintw(help_win_, 5, 1, "* portfolios   Show the list of portfolios");
	mvwprintw(help_win_, 6, 1, "* select       Select a portfolio");
	mvwprintw(help_win_, 7, 1, "* create       Create a portfolio");
	mvwprintw(help_win_, 8, 1, "* help         Show this dialog");
	mvwprintw(help_win_, 9, 1, "* save         Save to a file");
	mvwprintw(help_win_, 10, 1, "* load         Load from a file");
	mvwprintw(help_win_, 11, 1, "* exit         Exit the program");
	wrefresh(help_win_);
	getch();
	hide_help();
}

void view_curses::hide_help() {
	delwin(help_win_);
	touchwin(main_list_);
	wrefresh(main_list_);
	touchwin(prompt_);
	wrefresh(prompt_);
}

void view_curses::setup_colors() const {
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	init_pair(2, COLOR_RED, COLOR_BLACK);
}

void view_curses::teardown() {
	nodelay(stdscr, false);
	delwin(prompt_);
	delwin(main_list_);
	delwin(status_bar_);
	endwin();
}
