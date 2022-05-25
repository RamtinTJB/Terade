#include <iostream>
#include <memory>

#include "view_curses.h"
#include "game.h"
#include "options.h"

int main(int argc, const char** argv) {
	options opt = parse_opt(argc, argv);
	if (!opt.valid) {
		std::cout << usage(argv[0]) << std::endl;
		return -1;
	}

	if (opt.help) {
		std::cout << help(argv[0]) << std::endl;
		return 0;
	}
	game g(opt.file_path);
	g.set_view(std::unique_ptr<view>(new view_curses));
	g.start();

	return 0;
}
