#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Mutator {
public:
	virtual void operator()(Population& population) = 0;
	static std::shared_ptr<Mutator> produce(const common::MutationOptions& options);
};

typedef std::shared_ptr<Mutator> MutatorPtr;

} // namespace model
