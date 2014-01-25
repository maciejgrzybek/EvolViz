#pragma once
#include <memory>
#include <string>
#include "ModelOptions.h"
#include "FitnessFunctionCalculator.h"

namespace model {

struct Population;

class FitnessFunctioner {
public:
	virtual void operator()(Population& population) = 0;
	static std::shared_ptr<FitnessFunctioner> produce(const std::string& formula);
};

class FitnessFunctionerImpl : public FitnessFunctioner, public common::FitnessFunctionCalculator {
public: 
	FitnessFunctionerImpl(const std::string& formula);
	virtual void operator()(Population& population) override;
};

typedef std::shared_ptr<FitnessFunctioner> FitnessFunctionerPtr;

} // namespace model
