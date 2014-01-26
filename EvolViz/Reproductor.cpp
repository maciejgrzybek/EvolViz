#include "Reproductor.h"
#include "Population.h"
#include "EvolFunctions.hpp"
#include <cmath>

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
	unsigned int create = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * rate_));
	while (create--)
		population.subjects.push_back(population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)]);
}

} // namespace model
