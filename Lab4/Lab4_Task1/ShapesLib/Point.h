#pragma once

struct Point
{
	float x;
	float y;
};

inline bool operator==(const Point& left, const Point& right)
{
	return std::tie(left.x, left.y) == std::tie(right.x, right.y);
}