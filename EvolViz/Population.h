#pragma once
#include <vector>

namespace model {

struct Population
{
	struct Subject {
		double x;
		double y;
		double value;

        bool operator< (const Subject& other) const;
        bool operator==(const Subject& other) const;
        bool operator<=(const Subject& other) const;
        bool operator> (const Subject& other) const;
        bool operator>=(const Subject& other) const;
        bool operator!=(const Subject& other) const;
	};
	std::vector<Subject> subjects;
};

}
