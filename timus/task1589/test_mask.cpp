
#include <gtest/gtest.h>
#include "mask.h"


TEST(Mask, UnsetByDefault) {
	Mask<int, 0, 4> m;

	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			ASSERT_FALSE(m.get(x, y));
		}
	}
}


TEST(Mask, SetReset) {
	Mask<int, 0, 4> m;
	m.set(2, 2);
	ASSERT_TRUE(m.get(2, 2));

	m.set(2, 2, false);
	ASSERT_FALSE(m.get(2, 2));
}


template <class M>
static void _check_row(const M& m, int row) {
	for (int x = M::Offset; x < M::Max; ++x) {
		for (int y = M::Offset; y < M::Max; ++y) {
			ASSERT_EQ(row == x, m.get(x, y));
		}
	}
}


TEST(Mask, SetResetWithOffset) {
	Mask<int, 5, 4> m;

	for (int x = 5; x < 9; ++x) {
		for (int y = 5; y < 9; ++y) {
			m.set(x, y);
		}
		_check_row(m, x);

		for (int y = 5; y < 9; ++y) {
			m.reset(x, y);
		}
		_check_row(m, -1);
	}
}


TEST(Mask, SetCoords) {
	Mask<int, 0, 5, 2> m;

	m.set_coords(2, 1);

	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			m.set(x, y);
		}
	}

	int xx = 0;
	int yy = 0;
	m.get_coords(&xx, &yy);

	ASSERT_EQ(2, xx);
	ASSERT_EQ(1, yy);
}


