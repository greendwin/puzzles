
#include <stdio.h>
#include "level.h"

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


int main() {
	Level l;
	//level_load_from_file("input.txt", &l);
	level_load_from_file("level8.txt", &l);

	//run_game(l);
    //print_unreachable_cells(l);
	print_solution(l);
	return 0;
}
