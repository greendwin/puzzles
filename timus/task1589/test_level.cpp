
#include <gtest/gtest.h>
#include "level.h"

using namespace std;

#define COUNT_OF(A) int(sizeof(A) / sizeof(0[A]))


TEST(Level, LoadPosition) {
	Level l;
	
	level_load(
		"     \n"
		"  @  \n"
		"     \n",
		&l);

	int x, y;
	mask_get_coords(l.state, &x, &y);

	ASSERT_EQ(2, x);
	ASSERT_EQ(1, y);
}


TEST(Level, LoadWalls) {
	Level l;

	level_load(
		" ####\n"
		"##  #\n"
		"#####\n",
		&l);

	// empty corner
	ASSERT_FALSE(mask_get(l.walls, 0, 0));
	ASSERT_FALSE(mask_get(l.walls, 2, 1));
	ASSERT_FALSE(mask_get(l.walls, 3, 1));

	ASSERT_TRUE(mask_get(l.walls, 1, 0));
	ASSERT_TRUE(mask_get(l.walls, 1, 1));
	ASSERT_TRUE(mask_get(l.walls, 4, 2));
}


TEST(Level, LoadTargets) {
	Level l;

	level_load(
		"     \n"
		"  .. \n"
		"   . \n",
		&l);

	ASSERT_FALSE(mask_get(l.targets, 2, 2));

	ASSERT_TRUE(mask_get(l.targets, 2, 1));
	ASSERT_TRUE(mask_get(l.targets, 3, 1));
	ASSERT_TRUE(mask_get(l.targets, 3, 2));
}


TEST(Level, LoadTargetsWithPlayer) {
	Level l;

	level_load(
		"     \n"
		" .+. \n"
		"     \n",
		&l);

	ASSERT_TRUE(mask_get(l.targets, 2, 1));

	int x, y;
	mask_get_coords(l.state, &x, &y);
	ASSERT_EQ(2, x);
	ASSERT_EQ(1, y);
}


TEST(Level, LoadBox) {
	Level l;

	level_load(
		"     \n"
		"  $$ \n"
		"  $  \n",
		&l);

	ASSERT_TRUE(mask_get(l.state, 2, 1));
	ASSERT_TRUE(mask_get(l.state, 3, 1));
	ASSERT_TRUE(mask_get(l.state, 2, 2));
}


TEST(Level, LoadBoxOnTarget) {
	Level l;

	level_load(
		"     \n"
		" .*. \n"
		"     \n",
		&l);

	ASSERT_TRUE(mask_get(l.targets, 2, 1));
	ASSERT_TRUE(mask_get(l.state, 2, 1));
}


void _level_setup_test_level(Level* l)
{
	//	" ######\n"	// 0
	//	"##  $ #\n"	// 1
	//	"# @ $ #\n" // 2
	//	"#.... #\n" // 3
	//	"#######\n" // 4
	//	 0123456

	// add walls
	for (int x = 0; x < 7; ++x) {
		for (int y = 0; y < 7; ++y) {
			if (x == 0 || x == 6 || y == 0 || y == 4) {
				mask_set(l->walls, x, y);
			}
		}
	}

	// left corner
	mask_reset(l->walls, 0, 0);
	mask_set(l->walls, 1, 1);

	// position
	mask_set_coords(l->state, 2, 2);

	// blocks
	mask_set(l->state, 4, 1);
	mask_set(l->state, 4, 2);

	// targets
	mask_set(l->targets, 1, 3);
	mask_set(l->targets, 2, 3);
	mask_set(l->targets, 3, 3);
	mask_set(l->targets, 4, 3);
}


TEST(Level, Print) {
	Level l;
	_level_setup_test_level(&l);

	ostringstream output;
	level_print(l, output);

	const char* level_text[] = {
		" ######",
		"##  $ #",
		"# @ $ #",
		"#.... #",
		"#######",
	};

	istringstream input(output.str());
	string line;

	for (int y = 0; y < COUNT_OF(level_text); ++y) {
		getline(input, line);

		ASSERT_EQ(level_text[y], line);
	}
}


TEST(Level, PrintTargetWithPosBlock) {
	Level l;
	_level_setup_test_level(&l);

	// move player to target place
	mask_set_coords(l.state, 2, 3);

	// put target under the box
	mask_set(l.targets, 4, 2);

	ostringstream output;
	level_print(l, output);

	const char* level_text[] = {
		" ######",
		"##  $ #",
		"#   * #",
		"#.+.. #",
		"#######",
	};

	istringstream input(output.str());
	string line;

	for (int y = 0; y < COUNT_OF(level_text); ++y) {
		getline(input, line);

		ASSERT_EQ(level_text[y], line);
	}
}


// TODO: make interactive game
// TODO: search algorithm (for single box -- unreachable places mask)

