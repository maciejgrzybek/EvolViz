#pragma once
#include <memory>
#include <string>
#include "ModelOptions.h"

namespace model {

struct Population;

class FitnessFunctioner {
public:
	virtual void operator()(Population& population) = 0;
	static std::shared_ptr<FitnessFunctioner> produce(const std::string& formula);
};

typedef std::shared_ptr<FitnessFunctioner> FitnessFunctionerPtr;

} // namespace model
