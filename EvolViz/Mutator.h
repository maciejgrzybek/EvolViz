#pragma once
#include <memory>

namespace model {

struct Population;

class Mutator {
public:
	virtual void operator()(Population& population) = 0;
};

typedef std::shared_ptr<Mutator> MutatorPtr;

} // namespace model
