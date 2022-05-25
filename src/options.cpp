#include "options.h"

std::string usage(const char* program) {
	return std::string(program) + " [-h] [-L] [file]";
}

std::string help(const char* program) {
	return usage(program) + "\n\n"
		+ "Options: \n" +
		"   -h:    Show this text.\n" +
		"   -L:    Load the simulation from a file.";
}

options parse_opt(int argc, const char** argv) {
	options opt;
	int counter = 1;
	while (counter < argc) {
		if (std::strcmp(argv[counter], "-h") == 0) {
			opt.help = true;
		} else if (std::strcmp(argv[counter], "-L") == 0) {
			counter++;
			if (counter >= argc) {
				opt.valid = false;
				return opt;
			}
			opt.file_path = std::string(argv[counter]);
		} else {
			opt.valid = false;
			return opt;
		}
		counter++;
	}
	return opt;
}
