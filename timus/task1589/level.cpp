#include <cstdio>
#include <fstream>

#include "level.h"

using namespace std;


void load_level_from_file(const char* filename, Level* level) {
	ifstream input{filename};
	load_level(input, level);
}


void _parse_line(Level* level, int row, string& line) {
	for (int k = 0; k < (int)line.size(); ++k) {
		char ch = line[k];

		switch (ch) {
			case '#':
				level->walls.set(k, row);
				break;

			case '.':
				level->targets.set(k, row);
				break;

			case '@':
				level->state.set_coords(k, row);
				break;

			case '+':
				level->targets.set(k, row);
				level->state.set_coords(k, row);
				break;

			case '$':
				level->state.set(k, row);
				break;

			case '*':
				level->targets.set(k, row);
				level->state.set(k, row);
				break;
		}
	}
}


void load_level(istream& input, Level* level) {
	string line;
	int row = 0;
	while (getline(input, line)) {
		_parse_line(level, row, line);
	}
}
