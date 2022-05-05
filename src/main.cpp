#include <iostream>
#include <memory>

#include "asset.h"
#include "view_curses.h"
#include "api.h"
#include "game.h"

int main(int argc, char** argv) {
	game g;
	g.set_view(std::unique_ptr<view>(new view_curses));
	g.start();

	return 0;
}
