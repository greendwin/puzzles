
#include <gtest/gtest.h>
#include "level.h"


TEST(Search, FillField) {
	Level l;
	level_load(
		"######\n"
		"# @#.#\n"
		"#  # #\n"
		"#  $ #\n"
		"######\n",
		&l);

	StateMask fill;
	level_mark_reachable(l, &fill);

	ASSERT_TRUE(mask_get(fill, 1, 1));
	ASSERT_TRUE(mask_get(fill, 2, 2));
	ASSERT_TRUE(mask_get(fill, 1, 3));

	ASSERT_FALSE(mask_get(fill, 4, 1));
	ASSERT_FALSE(mask_get(fill, 4, 2));
	ASSERT_FALSE(mask_get(fill, 4, 3));
}


TEST(Search, NormalizePosition) {
	Level l;
	level_load(
		"######\n"
		"# @#.#\n"
		"#  # #\n"
		"#  $ #\n"
		"######\n",
		&l);

	StateMask fill;
	level_mark_reachable(l, &fill);

	int x, y;
	mask_get_coords(fill, &x, &y);

	ASSERT_EQ(1, x);
	ASSERT_EQ(1, y);
}


TEST(Search, IsDeadPosition) {
	Level l;
	level_load(
		"######\n"
		"#!@#.#\n"
		"# ?# #\n"
		"#!?? #\n"
		"### !#\n"
		"######\n",
		&l);

	// check that box placed to this coord can be moved to target
	ASSERT_TRUE(level_is_dead_position(l, 1, 1));
	ASSERT_TRUE(level_is_dead_position(l, 1, 4));
	ASSERT_TRUE(level_is_dead_position(l, 4, 4));

	ASSERT_FALSE(level_is_dead_position(l, 2, 2));
	ASSERT_FALSE(level_is_dead_position(l, 2, 3));
	ASSERT_FALSE(level_is_dead_position(l, 3, 3));
}

