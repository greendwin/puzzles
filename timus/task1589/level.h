#ifndef __LEVEL_H__
#define __LEVEL_H__


#include <iostream>
#include <unordered_set>
#include <vector>

#ifndef ONLINE_JUDGE
#include "mask.h"
#endif


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


const int direction_count = 4;
extern int direction_dx[];
extern int direction_dy[];


enum class MoveResult {
	Moved,
	MovedBlock,
	Blocked,
};


struct SolveStep {
	int x;
	int y;
	Direction dir;

	SolveStep(int x, int y, Direction dir)
		: x(x), y(y), dir(dir)
	{}
};

using SolvePath = std::vector<SolveStep>;


struct Level {
	WallMask walls;
	TargetsMask targets;
	StateMask state; 
};


void level_load_from_file(const char* filename, Level* level);
void level_load(const char* input, Level* level);
void level_load(std::istream& input, Level* level);

void level_print(const Level& level, std::ostream& output, const StateMask* overlay = nullptr, char overlaySymbol = 'x');


LevelItem level_look_at(const Level& level, Direction dir);
LevelItem level_look_at(const Level& level, int x, int y);

MoveResult level_move_to(Level& level, Direction dir);
bool level_move_to(Level level, int x, int y, SolvePath* path);

bool level_is_finish_state(StateMask state, TargetsMask targets);
inline bool level_is_finish_state(const Level& level) { return level_is_finish_state(level.state, level.targets); }


void level_mark_reachable(const Level& level, StateMask* mask);
bool level_is_dead_position(const Level& level, int x, int y);
void level_mark_deadends(const Level& level, StateMask* mask);
bool level_solve(const Level& level, SolvePath* path);


using VisitedStates = std::unordered_set<uint64_t>;
inline void visited_state_add(VisitedStates& cont, StateMask state) { cont.insert(state.data); }
inline bool visited_state_is(const VisitedStates& cont, StateMask state) { return cont.find(state.data) != cont.end(); }


struct SolveContext {
	SolvePath path;
	StateMask deadend;
};


#endif // __LEVEL_H__
