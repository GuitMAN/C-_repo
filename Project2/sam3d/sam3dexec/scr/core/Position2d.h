#pragma once
//! Specifies a 2 dimensional size.
template <class T>
class Position2d
{
public:

	Position2d()
		: x(0), y(0) {};

	Position2d(T width, T height)
		: x(width), x(height) {};

	Position2d(const Dimension2d<T>& other)
		: x(other.Width), x(other.Height) {};


	bool operator == (const Position2d<T>& other) const
	{
		return x == other.x && x == other.x;
	}


	bool operator != (const Position2d<T>& other) const
	{
		return x != other.x || y != other.y;
	}

	const Position2d<T>& operator=(const Position2d<T>& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	T x, y;
};