#ifndef TERADE_UTILS_H
#define TERADE_UTILS_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <locale>
#include <cctype>

#include "asset.h"

template <class K, class V>
bool map_contains(const std::map<K, V>& m, const K& key) {
	return m.count(key) == 1;
}

bool is_num(const std::string& str);
std::string prettify_double(const double num, int precision = 2);
std::string prettify_price(const double price);
std::string upper_case_str(const std::string& str);

template <class T>
std::vector<std::string> format(const std::vector<T>& vect,
		std::function<std::string(const T&)> formatter) {
	std::vector<std::string> res;
	for (const auto& item: vect) {
		res.push_back(formatter(item));
	}
	return res;
}

#endif
