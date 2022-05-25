#include "game.h"

bool is_num(const std::string& str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

std::string prettify_double(const double num, int precision) {
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::fixed << std::showpoint << std::setprecision(precision);
	ss << num;
	return ss.str();
}

std::string prettify_price(const double price) {
	if (price < 1) {
		return prettify_double(price, 4);
	} else {
		return prettify_double(price);
	}
}

std::string upper_case_str(const std::string& str) {
	std::string res;
	for (const auto& c: str) {
		res.push_back(std::toupper(c));
	}
	return res;
}
