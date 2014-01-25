#pragma once
#include <vector>

namespace model {

struct Population
{
	struct Subject {
		double x;
		double y;
		double value;

		bool operator< (const Subject& other);		
		bool operator==(const Subject& other);
		bool operator<=(const Subject& other);
		bool operator> (const Subject& other);
		bool operator>=(const Subject& other);
		bool operator!=(const Subject& other);
	};
	std::vector<Subject> subjects;
};

}
