#pragma once
#include <memory>

namespace model {

class Selector {
public:
	virtual void operator()(Population& population, unsigned int size) = 0;
};

typedef std::shared_ptr<Selector> SelectorPtr;

} // namespace model
