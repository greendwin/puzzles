#pragma once

#include <iostream>
#include "mask.h"


using WallMask = Mask<uint64_t, 0, 8>;
using TargetsMask = Mask<uint64_t, 1, 6>;
using StateMask = Mask<uint64_t, 1, 6, 3>;


struct Level {
	WallMask walls;
	TargetsMask targets;
	StateMask state; 
};


void level_load_from_file(const char* filename, Level* level);
void level_load(const char* input, Level* level);
void level_load(std::istream& input, Level* level);

