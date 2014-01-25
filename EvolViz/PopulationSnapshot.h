#pragma once
#include <vector>

namespace model {

struct PopulationSnapshot
{
	struct Subject {
		double x;
		double y;
		double value;
	};
	std::vector<Subject> subjects;
};

}
