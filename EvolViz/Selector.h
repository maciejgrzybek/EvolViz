#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Selector {
public:
	virtual void operator()(Population& population, unsigned int size) = 0;
	static std::shared_ptr<Selector> produce(const common::SelectionType options);
};

typedef std::shared_ptr<Selector> SelectorPtr;

} // namespace model
