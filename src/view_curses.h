#ifndef TERADE_VIEW_CURSES_H
#define TERADE_VIEW_CURSES_H

#include <string>
#include <ncurses.h>
#include <memory>

#include "view.h"
#include "asset.h"
#include "utils.h"

class view_curses : public view {
	public:
		view_curses() {
			setup();
		}

		~view_curses() {
			teardown();
		}

		void update_list(const std::vector<std::string>&, const std::string&) override;
		void set_list_title(const std::string& title) override;
		void update_status_bar(const player& p) override;
		std::string get_entry() override;
		std::string get_input(const std::string& prompt) override;
		void show_error(const std::string& error_msg) override;
		void show_help() override;
		void hide_help() override;

		void teardown() override;

		void getchar() override { getch(); }

	private:
		WINDOW* prompt_ = nullptr;
		WINDOW* main_list_ = nullptr;
		WINDOW* status_bar_ = nullptr;
		WINDOW* input_win = nullptr;
		WINDOW* help_win_ = nullptr;
		int maxheight_ = 24;
		int maxwidth_ = 80;
		int prompt_ht = 5;
		int prompt_wd = maxwidth_;
		int list_ht = 19;
		int list_wd = maxwidth_;
		int status_ht = 1;
		int status_wd = maxwidth_;
		int input_ht = 3;
		int input_wd = 20;
		int help_ht = 13;
		int help_wd = 50;

		char clear_line_[75];

		void clear_list();

		void setup();

		void setup_prompt();
		void setup_main_list();
		void setup_status_bar();

		void setup_colors() const;

		void set_color() const;

		std::string get_input_curses(const std::string& prompt);
};

#endif
