
#include <gtest/gtest.h>
#include "level.h"

using namespace std;


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

// TODO: print level (we can make fewer tests, since it would be used only for preview)

