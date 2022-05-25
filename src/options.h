#ifndef TERADE_OPTIONS_H
#define TERADE_OPTIONS_H

#include <string>
#include <iostream>

struct options {
	std::string file_path;
	bool help = false;
	bool valid = true;
};

std::string usage(const char* program);
std::string help(const char* program);

options parse_opt(int argc, const char** argv);

#endif
