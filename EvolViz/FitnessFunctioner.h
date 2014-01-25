#pragma once
#include <memory>

namespace model {

struct Population;

class FitnessFunctioner {
public:
	virtual void operator()(Population& population) = 0;
};

typedef std::shared_ptr<FitnessFunctioner> FitnessFunctionerPtr;

} // namespace model
