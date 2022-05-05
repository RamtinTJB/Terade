#ifndef TERADE_UTILS_H
#define TERADE_UTILS_H

#include <map>
#include <vector>
#include <string>

template <class K, class V>
bool map_contains(const std::map<K, V>& m, const K& key) {
	return m.count(key) == 1;
}

bool is_num(const std::string& str);

#endif
