#pragma once

#include <cassert>


template <
	class DataType,
	int FieldOffset,
	int FieldSize,
	int CoordBits = 0		// per coord
>
struct Mask {
	static_assert(FieldSize * FieldSize + 2 * CoordBits <= 8 * sizeof(DataType));

	DataType data;

	Mask(void)
		: data(0)
	{}

	static constexpr DataType shift_bit(int count) {
		return (DataType)1 << count;
	}

	static constexpr DataType get_mask(int count) {
		return shift_bit(count) - 1;
	}

	void set(int x, int y, bool v = true) {
		assert(FieldOffset <= x && x < FieldOffset + FieldSize);
		assert(FieldOffset <= y && y < FieldOffset + FieldSize);
	
		int bit = (x - FieldOffset) * FieldSize + (y - FieldOffset);
		if (v) {
			data |= shift_bit(bit);
		} else {
			data &= ~shift_bit(bit);
		}
	}

	bool get(int x, int y) {
		assert(FieldOffset <= x && x < FieldOffset + FieldSize);
		assert(FieldOffset <= y && y < FieldOffset + FieldSize);
	
		int bit = (x - FieldOffset) * FieldSize + (y - FieldOffset);
		return data & shift_bit(bit);
	}

	void set_coords(int x, int y) {
		assert(0 <= x && x < (1 << CoordBits));
		assert(0 <= y && y < (1 << CoordBits));

		int field_offset = FieldSize * FieldSize;
		
		// reset prev coords
		DataType coords_mask = get_mask(2 * CoordBits);	// 00001111
		data &= ~(coords_mask << field_offset);

		// xxyy0000
		data |= (DataType)x << (field_offset + CoordBits);
		data |= (DataType)y << field_offset;
	}

	void get_coords(int * x, int * y) {
		int field_offset = FieldSize * FieldSize;
		DataType xx = data >> (field_offset + CoordBits);
		DataType yy = data >> field_offset;

		DataType coord_mask = get_mask(CoordBits);
		*x &= int(xx & coord_mask);
		*y &= int(yy & coord_mask);
	}
};

