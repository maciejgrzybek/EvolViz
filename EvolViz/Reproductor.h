#pragma once
#include <memory>

namespace model {

struct Population;

class Reproductor {
public:
	virtual void operator()(Population& population) = 0;
};

typedef std::shared_ptr<Reproductor> ReproductorPtr;

} // namespace model
