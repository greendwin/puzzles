
#include <stdio.h>

#ifndef ONLINE_JUDGE
#include "level.h"
#endif

using namespace std;


void run_game(Level& l) {
	string line;
	for (;;) {
		level_print(l, cout);
		if (level_is_finish_state(l)) {
			cout << "Puzzle complete!\n";
			return;
		}

		bool r = getline(cin, line);
		if (!r) {
			break;
		}

		for (int idx = 0; idx < (int)line.size(); ++idx) {
			char ch = line[idx];

			if (ch == 'r') {
				level_move_to(l, Direction::Right); 
			} else if (ch == 'l') {
				level_move_to(l, Direction::Left); 
			} else if (ch == 'u') {
				level_move_to(l, Direction::Up); 
			} else if (ch == 'd') {
				level_move_to(l, Direction::Down); 
			} else if (ch == 'q') {
				cout << "Exit game\n";
				return;
			} else {
				cout << "Unknown command, use r, l, u, d and q\n";
				break;
			}
		}
	}
}


void print_unreachable_cells(const Level& level) {
	StateMask unreachable;
	level_mark_deadends(level, &unreachable);

	level_print(level, cout, &unreachable);
}


void print_solution(Level level) {
	SolvePath path;
	level_solve(level, &path);

	// initial
	level_print(level, cout);

	for (int k = 0; k < (int)path.size(); ++k) {
		SolveStep step = path[k];
		int plrX = step.x - direction_dx[(int)step.dir];
		int plrY = step.y - direction_dy[(int)step.dir];

		mask_set_coords(level.state, plrX, plrY);
		level_move_to(level, step.dir);
		getchar();
		cout << "-\n";
		level_print(level, cout);
	}
}


void print_solution_by_steps(Level level) {
	SolvePath path;
	level_solve(level, &path);

	// initial
	level_print(level, cout);

	for (int k = 0; k < (int)path.size(); ++k) {
		int curX, curY;
		mask_get_coords(level.state, &curX, &curY);

		SolveStep step = path[k];
		int plrX = step.x - direction_dx[(int)step.dir];
		int plrY = step.y - direction_dy[(int)step.dir];

		if (curX != plrX || curY != plrY) {
			// emit intermediate movement steps
			SolvePath movePath;
			level_move_to(level, plrX, plrY, &movePath);

			for (int kkk = 0; kkk < (int)movePath.size(); ++kkk) {
				level_move_to(level, movePath[kkk].dir);
				
				getchar();
				cout << "-\n";
				level_print(level, cout);
			}
		}

		// move block
		level_move_to(level, step.dir);
		getchar();
		cout << "-\n";
		level_print(level, cout);
	}
}


static void _print_dir(Direction dir, bool blockMoved) {
	switch (dir) {
		case Direction::Left:
			cout << (blockMoved ? "L" : "l");
			break;
		case Direction::Right:
			cout << (blockMoved ? "R" : "r");
			break;
		case Direction::Up:
			cout << (blockMoved ? "U" : "u");
			break;
		case Direction::Down:
			cout << (blockMoved ? "D" : "d");
			break;
	}
}


void print_timus(Level level) {
	SolvePath path;
	level_solve(level, &path);

	for (int k = 0; k < (int)path.size(); ++k) {
		int curX, curY;
		mask_get_coords(level.state, &curX, &curY);

		SolveStep step = path[k];
		int plrX = step.x - direction_dx[(int)step.dir];
		int plrY = step.y - direction_dy[(int)step.dir];

		if (curX != plrX || curY != plrY) {
			// emit intermediate movement steps
			SolvePath movePath;
			level_move_to(level, plrX, plrY, &movePath);

			for (int kkk = 0; kkk < (int)movePath.size(); ++kkk) {
				level_move_to(level, movePath[kkk].dir);
				_print_dir(movePath[kkk].dir, false);
			}
		}

		// move block
		level_move_to(level, step.dir);
		_print_dir(step.dir, true);
	}

	cout << endl;
}


int main() {
	Level l;

#ifdef ONLINE_JUDGE
	level_load(cin, &l);
	print_timus(l);
#else
	level_load_from_file("input2.txt", &l);
	//level_load_from_file("level8.txt", &l);

	//run_game(l);
    //print_unreachable_cells(l);
	//print_solution(l);
	print_solution_by_steps(l);
#endif

	return 0;
}
