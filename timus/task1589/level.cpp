#include <cstdio>
#include <fstream>
#include <sstream>

#include "level.h"

using namespace std;


void level_load_from_file(const char* filename, Level* level) {
	ifstream input{filename};
	level_load(input, level);
}


void level_load(const char* field, Level* level) {
	istringstream input{field};
	level_load(input, level);
}


static void _level_parse_line(Level* level, int row, string& line) {
	for (int k = 0; k < (int)line.size(); ++k) {
		char ch = line[k];

		switch (ch) {
			case '#':
				mask_set(level->walls, k, row);
				break;

			case '.':
				mask_set(level->targets, k, row);
				break;

			case '@':
				mask_set_coords(level->state, k, row);
				break;

			case '+':
				mask_set(level->targets, k, row);
				mask_set_coords(level->state, k, row);
				break;

			case '$':
				mask_set(level->state, k, row);
				break;

			case '*':
				mask_set(level->targets, k, row);
				mask_set(level->state, k, row);
				break;
		}
	}
}


void level_load(istream& input, Level* level) {
	string line;
	int row = 0;
	while (getline(input, line)) {
		_level_parse_line(level, row, line);
		++row;
	}
}
