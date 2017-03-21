#pragma once

#include <iostream>
#include "mask.h"


using WallMask = Mask<uint64_t, 0, 8>;
using TargetsMask = Mask<uint64_t, 1, 6>;
using StateMask = Mask<uint64_t, 1, 6, 3>;


enum class LevelItem {
	Empty,
	Block,
	Wall,
};


enum class Direction {
	Left,
	Up,
	Right,
	Down,
};

extern int direction_dx[];
extern int direction_dy[];


enum class MoveResult {
	Moved,
	MovedBlock,
	Blocked,
};


struct Level {
	WallMask walls;
	TargetsMask targets;
	StateMask state; 
};


void level_load_from_file(const char* filename, Level* level);
void level_load(const char* input, Level* level);
void level_load(std::istream& input, Level* level);

void level_print(const Level& level, std::ostream& output);

LevelItem level_look_at(const Level& level, Direction dir);
LevelItem level_look_at(const Level& level, int x, int y);

MoveResult level_move_to(Level& level, Direction dir);
