#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Crosser {
public:
	virtual void operator()(Population& population) = 0;
	static std::shared_ptr<Crosser> produce(const common::CrossOverOptions& options);
};

typedef std::shared_ptr<Crosser> CrosserPtr;

} // namespace model
