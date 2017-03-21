
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


void print_unreachable_cells(const Level& level_) {
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

	level_print(level_, cout, &unreachable);
}


int main() {
	Level l;
	level_load_from_file("input.txt", &l);

//	run_game(l);
    print_unreachable_cells(l);
	return 0;
}
