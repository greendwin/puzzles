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


static void _level_calc_field_size(const Level& level, int* sizeX, int* sizeY) {
	// detect size by walls
	int xxx	= 0;
	int yyy = 0;
	for (int y = 0; y < WallMask::Max; ++y) {
		for (int x = 0; x < WallMask::Max; ++x) {
			if (mask_get(level.walls, x, y)) {
				if (xxx < x) {
					xxx = x;
				}
				if (yyy < y) {
					yyy = y;
				}
			}
		}
	}

	*sizeX = xxx + 1;
	*sizeY = yyy + 1;
}


void level_print(const Level& level, ostream& output) {
	int sizeX, sizeY;
	_level_calc_field_size(level, &sizeX, &sizeY);

	int posX, posY;
	mask_get_coords(level.state, &posX, &posY);

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			// wall
			if (mask_get(level.walls, x, y)) {
				output << '#';
				continue;
			}

			bool is_target = mask_get(level.targets, x, y);

			// block
			if (mask_get(level.state, x, y)) {
				output << (is_target ? '*' : '$');
				continue;
			}

			// player
			if (x == posX && y == posY) {
				output << (is_target ? '+' : '@');
				continue;
			}

			// empty target
			if (is_target) {
				output << '.';
				continue;
			}

			// otherwise empty space
			output << ' ';
		}
		output << '\n';
	}
}

