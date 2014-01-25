#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Alignator {
public:
	virtual void operator()(Population& population) = 0;
	static std::shared_ptr<Alignator> produce(const common::RangeAlignmentOptions& options);
};

typedef std::shared_ptr<Alignator> AlignatorPtr;

} // namespace model
