#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Initializer {
public:
	virtual void operator()(Population& population, unsigned int size) = 0;
	static std::shared_ptr<Initializer> produce(const common::InitializationOptions& options);
};

typedef std::shared_ptr<Initializer> InitializerPtr;

} // namespace model
