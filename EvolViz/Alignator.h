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

class RollingAlignator : public Alignator {
	
};

class MirroringRangeAlignator : public Alignator {
};

class ReinitializationAlignator : public Alignator {
};

typedef std::shared_ptr<Alignator> AlignatorPtr;

} // namespace model
