#pragma once
#include <memory>

namespace model {

struct Population;

class Crosser {
public:
	virtual void operator()(Population& population) = 0;
};

typedef std::shared_ptr<Crosser> CrosserPtr;

} // namespace model
