#include "Reproductor.h"
namespace model {

ReproductorPtr Reproductor::produce(const common::ReproductionOptions& options) {
	return ReproductorPtr(new ReproductorImpl(options.rate));
}

Reproductor::Reproductor(const double rate)
	: rate_(rate) {
}

ReproductorImpl::ReproductorImpl(const double rate)
	: Reproductor(rate) {
}

void ReproductorImpl::operator()(Population& population) const {
	// FIXME implement this
}

} // namespace model
