#include <cstdio>
#include <fstream>
#include <sstream>

#ifndef ONLINE_JUDGE
#include "level.h"
#endif

using namespace std;


int direction_dx[] = { -1, 0, 1, 0 };
int direction_dy[] = { 0, -1, 0, 1 };


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


void level_print(const Level& level, ostream& output, const StateMask* overlay, char overlaySymbol) {
	int sizeX, sizeY;
	_level_calc_field_size(level, &sizeX, &sizeY);

	int posX, posY;
	mask_get_coords(level.state, &posX, &posY);

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			if (overlay && mask_get(*overlay, x, y)) {
				output << overlaySymbol;
				continue;
			}

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


LevelItem level_look_at(const Level& level, Direction dir) {
	int posX, posY;
	mask_get_coords(level.state, &posX, &posY);

	posX += direction_dx[(int)dir];
	posY += direction_dy[(int)dir];

	return level_look_at(level, posX, posY);
}


LevelItem level_look_at(const Level& level, int x, int y) {
	if (mask_get(level.walls, x, y)) {
		return LevelItem::Wall;
	}

	if (mask_get(level.state, x, y)) {
		return LevelItem::Block;
	}

	return LevelItem::Empty;
}


MoveResult level_move_to(Level& level, Direction dir) {
	LevelItem next = level_look_at(level, dir);
	if (next == LevelItem::Wall) {
		// cannot move here
		return MoveResult::Blocked;
	}

	if (next == LevelItem::Empty) {
		int posX, posY;
		mask_get_coords(level.state, &posX, &posY);

		posX += direction_dx[(int)dir];
		posY += direction_dy[(int)dir];
		mask_set_coords(level.state, posX, posY);

		return MoveResult::Moved;
	}

	assert(next == LevelItem::Block);

	// player pos
	int posX, posY;
	mask_get_coords(level.state, &posX, &posY);

	// new player pos
	int nextX = posX + direction_dx[(int)dir];
	int nextY = posY + direction_dy[(int)dir];

	// new block pos
	int blockX = nextX + direction_dx[(int)dir];
	int blockY = nextY + direction_dy[(int)dir];

	if (level_look_at(level, blockX, blockY) != LevelItem::Empty) {
		// cannot move this block
		return MoveResult::Blocked;
	}

	// set player pos
	mask_set_coords(level.state, nextX, nextY);

	// move block
	mask_reset(level.state, nextX, nextY);
	mask_set(level.state, blockX, blockY);

	return MoveResult::MovedBlock;
}


bool level_is_finish_state(StateMask state, TargetsMask targets) {
	// check that every box is on the target
	for (int x = StateMask::Offset; x < StateMask::Max; ++x) {
		for (int y = StateMask::Offset; y < StateMask::Max; ++y) {
			if (mask_get(state, x, y) and !mask_get(targets, x, y)) {
				return false;
			}
		}
	}

	return true;
}

