#include "FitnessFunctioner.h"
#include "Population.h"

namespace model {
std::shared_ptr<FitnessFunctioner> FitnessFunctioner::produce(const std::string& formula) {
	return std::shared_ptr<FitnessFunctioner>(new FitnessFunctionerImpl(formula));
}

FitnessFunctionerImpl::FitnessFunctionerImpl(const std::string& formula)
	: common::FitnessFunctionCalculator(formula) {
}

void FitnessFunctionerImpl::operator()(Population& population) {
	for (Population::Subject& subject : population.subjects)
		subject.value = static_cast<FitnessFunctionCalculator&>(*this)(subject.x, subject.y);
}

} // namespace model