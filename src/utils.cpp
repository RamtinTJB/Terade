#include "game.h"

bool is_num(const std::string& str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}
