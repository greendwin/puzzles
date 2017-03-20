#pragma once

#include <cassert>


template <
	class _DataType,
	int _Offset,
	int _Dimension,
	int _CoordBits = 0		// per coord
>
struct Mask {
	using DataType = _DataType;

	static const int Offset = _Offset;
	static const int Dimension = _Dimension;
	static const int Max = Offset + Dimension;
	static const int CoordBits = _CoordBits;

	static_assert(Dimension * Dimension + 2 * CoordBits <= 8 * sizeof(DataType));

	DataType data;

	Mask(void)
		: data(0)
	{}

	// small helpers
	static constexpr DataType _shift_bit(int count) { return (DataType)1 << count; }
	static constexpr DataType _get_mask(int count)  { return _shift_bit(count) - 1; }
};


template <class M>
void mask_set(M& m, int x, int y, bool v = true) {
	assert(M::Offset <= x && x < M::Max);
	assert(M::Offset <= y && y < M::Max);
	
	int bit = (x - M::Offset) * M::Dimension + (y - M::Offset);
	if (v) {
		m.data |= m._shift_bit(bit);
	} else {
		m.data &= ~m._shift_bit(bit);
	}
}


template <class M>
void mask_reset(M& m, int x, int y) {
	mask_set(m, x, y, false);
}


template <class M>
bool mask_get(const M& m, int x, int y) {
	assert(M::Offset <= x && x < M::Max);
	assert(M::Offset <= y && y < M::Max);
	
	int bit = (x - M::Offset) * M::Dimension + (y - M::Offset);
	return m.data & m._shift_bit(bit);
}


template <class M>
void mask_set_coords(M& m, int x, int y) {
	assert(0 <= x && x < (1 << M::CoordBits));
	assert(0 <= y && y < (1 << M::CoordBits));

	using DataType = typename M::DataType;
	int field_offset = M::Dimension * M::Dimension;
		
	// reset prev coords
	DataType coords_mask = m._get_mask(2 * M::CoordBits);	// 00001111
	m.data &= ~(coords_mask << field_offset);

	// xxyy0000
	m.data |= (DataType)x << (field_offset + M::CoordBits);
	m.data |= (DataType)y << field_offset;
}


template <class M>
void mask_get_coords(const M& m, int* x, int* y) {
	using DataType = typename M::DataType;

	int field_offset = M::Dimension * M::Dimension;
	DataType xx = m.data >> (field_offset + M::CoordBits);
	DataType yy = m.data >> field_offset;

	DataType coord_mask = m._get_mask(M::CoordBits);
	*x = int(xx & coord_mask);
	*y = int(yy & coord_mask);
}

