
#include <queue>
#include <algorithm>

#ifndef ONLINE_JUDGE
#include "level.h"
#endif

using namespace std;


static void _level_mark(const Level& level, int x, int y, StateMask& mask) {
	mask_set(mask, x, y);

	for (int k = 0; k < direction_count; ++k) {
		int nextX = x + direction_dx[k];
		int nextY = y + direction_dy[k];

		if (level_look_at(level, nextX, nextY) != LevelItem::Empty) {
			continue;
		}

		if (mask_get(mask, nextX, nextY)) {
			// already was there
			continue;
		}

		_level_mark(level, nextX, nextY, mask);
	}
}


void level_mark_reachable(const Level& level, StateMask* mask) {
	int x, y;
	mask_get_coords(level.state, &x, &y);

	StateMask field;
	_level_mark(level, x, y, field);

	// get normalized position
	for (int x = StateMask::Offset; x < StateMask::Max; ++x) {
		for (int y = StateMask::Offset; y < StateMask::Max; ++y) {
			if (mask_get(field, x, y)) {
				mask_set_coords(field, x, y);
				goto DONE;
			}
		}
	}
DONE:

	*mask = field;
}


static bool _level_solve(Level level, VisitedStates& visited, SolveContext* ctx) {
	// check whether we in win state
	if (level_is_finish_state(level.state, level.targets)) {
		return true;
	}

	// mark reachable positions
	StateMask reachable;
	level_mark_reachable(level, &reachable);
	
	// set normalized position
	int x0, y0;
	mask_get_coords(reachable, &x0, &y0);
	mask_set_coords(level.state, x0, y0);

	// make sure that we here first time
	if (visited_state_is(visited, level.state)) {
		return false;
	}

	// mark current state as visited
	visited_state_add(visited, level.state);

	// iter over all boxes
	for (int x = StateMask::Offset; x < StateMask::Max; ++x) {
		for (int y = StateMask::Offset; y < StateMask::Max; ++y) {
			if (!mask_get(level.state, x, y)) {
				continue;
			}

			for (int dir = 0; dir < direction_count; ++dir) {
				int plrX = x - direction_dx[dir];
				int plrY = y - direction_dy[dir];

				// check whether we can come to this container to move it
				if (!mask_get(reachable, plrX, plrY)) {
					continue;
				}

				int boxX = x + direction_dx[dir];
				int boxY = y + direction_dy[dir];

				// check whether we can move the box to this direction
				if (level_look_at(level, boxX, boxY) != LevelItem::Empty) {
					continue;
				}

				// don't move boxes to deadends
				if (ctx != nullptr && mask_get(ctx->deadend, boxX, boxY)) {
					continue;
				}

				mask_set(level.state, boxX, boxY);
				mask_reset(level.state, x, y);
				mask_set_coords(level.state, x, y);

				if (ctx != nullptr) {
					// store step
					SolveStep step(x, y, (Direction)dir);

					ctx->path.push_back(step);
				}

				if (_level_solve(level, visited, ctx)) {
					return true;
				}

				// recover level state
				mask_reset(level.state, boxX, boxY);
				mask_set(level.state, x, y);
				mask_set_coords(level.state, x0, y0);

				if (ctx != nullptr) {
					ctx->path.pop_back();
				}
			}
		}
	}

	return false;
}


bool level_is_dead_position(const Level& level_, int x, int y) {
	Level level = level_;
	level.state = StateMask();
	mask_set(level.state, x, y);  // set only box

	StateMask visited;
	// try to place player
	for (int k = 0; k < direction_count; ++k) {
		int nextX = x + direction_dx[k];
		int nextY = y + direction_dy[k];

		if (mask_get(level.walls, nextX, nextY)) {
			continue;
		}

		if (mask_get(visited, nextX, nextY)) {
			continue;
		}

		// mark all positions reachable from this one
		_level_mark(level, nextX, nextY, visited);

		mask_set_coords(level.state, nextX, nextY);

		VisitedStates visited;
		if (_level_solve(level, visited, nullptr)) {
			return false;
		}
	}

	return true;
}


void level_mark_deadends(const Level& level_, StateMask* mask) {
	Level level = level_;

	// remove all boxes
	int plrX, plrY;
	mask_get_coords(level.state, &plrX, &plrY);
	level.state = StateMask();
	mask_set_coords(level.state, plrX, plrY);

	// mark all places, where player can move
	StateMask reachable;
	level_mark_reachable(level, &reachable);

	// mark unreachable cells
	StateMask unreachable;
	for (int x = StateMask::Offset; x < StateMask::Max; ++x) {
		for (int y = StateMask::Offset; y < StateMask::Max; ++y) {
			if (!mask_get(reachable, x, y)) {
				continue;
			}

			if (level_is_dead_position(level, x, y)) {
				mask_set(unreachable, x, y);
			}
		}
	}

	*mask = unreachable;
}


bool level_solve(const Level& level, SolvePath* path) {
	VisitedStates visited;
	SolveContext ctx;

	level_mark_deadends(level, &ctx.deadend);
	
	bool r = _level_solve(level, visited, &ctx);
	*path = std::move(ctx.path);

	return r;
}


bool level_move_to(Level level, int tgtX, int tgtY, SolvePath* path) {
	int x0, y0;
	mask_get_coords(level.state, &x0, &y0);

	// mark initial pos as visited and push it to queue
	StateMask visited;
	mask_set(visited, x0, y0);

	queue<StateMask> q;
	q.push(level.state);

	// allocate array for path restore
	vector<SolveStep> steps(WallMask::Max * WallMask::Max, SolveStep(0, 0, Direction::Left));

	while (!q.empty()) {
		level.state = q.front();
		q.pop();

		int x, y;
		mask_get_coords(level.state, &x, &y);

		if (x == tgtX && y == tgtY) {
			break;
		}

		for (int dir = 0; dir < direction_count; ++dir) {
			if (level_look_at(level, (Direction)dir) != LevelItem::Empty) {
				continue;
			}

			int nextX = x + direction_dx[dir];
			int nextY = y + direction_dy[dir];

			if (mask_get(visited, nextX, nextY)) {
				continue;
			}

			StateMask next_state = level.state;
			mask_set_coords(next_state, nextX, nextY);
			q.push(next_state);

			mask_set(visited, nextX, nextY);

			SolveStep step(x, y, (Direction)dir);
			steps[nextX * WallMask::Max + nextY] = step;
		}
	}

	// restore path
	int curX = tgtX;
	int curY = tgtY;

	SolvePath backtrack;
	while (curX != x0 || curY != y0) {
		SolveStep st = steps[curX * WallMask::Max + curY];
		backtrack.push_back(st);

		curX -= direction_dx[(int)st.dir];
		curY -= direction_dy[(int)st.dir];
	}

	reverse(backtrack.begin(), backtrack.end());
	*path = move(backtrack);

	return true;
}

