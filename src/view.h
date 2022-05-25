#ifndef TERADE_VIEW_H
#define TERADE_VIEW_H

#include <string>
#include <vector>

#include "asset.h"
#include "player.h"

class view {
	private:
		int width_;
		int height_;
	public:
		view() = default;
		view(int width, int height): width_{width}, height_{height} {};
		virtual ~view() = default;

		virtual void update_list(const std::vector<std::string>&, const std::string&) = 0;
		virtual void set_list_title(const std::string&) = 0;
		virtual void update_status_bar(const player& p) = 0;
		virtual std::string get_entry() = 0;
		virtual std::string get_input(const std::string& prompt) = 0;
		virtual void show_error(const std::string& error_msg) = 0;
		virtual void show_help() = 0;
		virtual void hide_help() = 0;
		virtual void getchar() = 0;

		virtual int width() const { return height_; }
		virtual int height() const { return width_; }

		virtual void teardown() = 0;
};

#endif
