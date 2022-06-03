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

// Returns true if the key exists in the map
template <class K, class V>
bool map_contains(const std::map<K, V>& m, const K& key) {
	return m.count(key) == 1;
}

// Checks if the string only contains numbers
// TODO: It should also return true if the string is a decimal number
bool is_num(const std::string& str);

/*
 * Round decimal number to the specified decimal point (precision) and
 * 		separate every 3 digits with a comma.
 * e.g. prettify_double(12345.6789, 2) returns 12,345.68
 */
std::string prettify_double(const double num, int precision = 2);

/*
 * If a price is more than $1, it will round it to 2 decimal points
 * 	otherwise, it will round it to 4 decimal points.
 */
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
