#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Reproductor {
public:
	Reproductor(const double rate);
	virtual void operator()(Population& population) const = 0;
	static std::shared_ptr<Reproductor> produce(const common::ReproductionOptions& options);

protected:
	const double rate_;
};

class ReproductorImpl : public Reproductor {
public:
	ReproductorImpl(const double rate);
	virtual void operator()(Population& population) const override;
};

typedef std::shared_ptr<Reproductor> ReproductorPtr;

} // namespace model