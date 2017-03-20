
#include <gtest/gtest.h>
#include "level.h"

using namespace std;


TEST(Level, Load_Position) {
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
