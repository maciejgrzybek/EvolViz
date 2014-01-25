#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Reproductor {
public:
	virtual void operator()(Population& population) = 0;
	static std::shared_ptr<Reproductor> produce(const common::ReproductionOptions& options);
};

typedef std::shared_ptr<Reproductor> ReproductorPtr;

} // namespace model