#pragma once
#include <memory>

namespace model {

struct Population;

class Initializer {
public:
	virtual void operator()(Population& population, unsigned int size) = 0;
};

typedef std::shared_ptr<Initializer> InitializerPtr;

} // namespace model
