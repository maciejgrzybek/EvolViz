#pragma once

#include <vector>

namespace common
{
	struct Point
	{
		double x;
		double y;
		double value;
	};

	struct GraphDescription
	{
		std::vector<Point> points;
	};

} // namespace common