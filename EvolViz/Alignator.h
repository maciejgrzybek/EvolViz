#pragma once
#include <memory>

namespace model {

struct Population;

class Alignator {
public:
	virtual void operator()(Population& population) = 0;
};

typedef std::shared_ptr<Alignator> AlignatorPtr;

} // namespace model
