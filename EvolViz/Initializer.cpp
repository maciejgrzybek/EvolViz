#include "Initializer.h"
#include "Population.h"
#include "EvolFunctions.hpp"

namespace model {

InitializerPtr Initializer::Factory::produce(const common::InitializationOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Initializer::Factory::visit(const common::PointInitialization& options) {
	last_produced_ = InitializerPtr(new PointInitializer(options.x, options.y));
}

void Initializer::Factory::visit(const common::RandomInitialization& options) {
	last_produced_ = InitializerPtr(new RandomInitializer(options.x_min, options.x_max, options.y_min, options.y_max));
}

PointInitializer::PointInitializer(const double x, const double y)
	: x_(x), y_(y) {
}

void PointInitializer::operator()(Population& population, unsigned int size) const {
	population.subjects.clear();
	while (size--)
		population.subjects.push_back({ x_, y_, 0.0 });
}

RandomInitializer::RandomInitializer(double x_min, double x_max, double y_min, double y_max)
	: x_min_(x_min), x_max_(x_max), y_min_(y_min), y_max_(y_max) {
}

void RandomInitializer::operator()(Population& population, unsigned int size) const {
	population.subjects.clear();
	while (size--)
		population.subjects.push_back({ evol::EvolFunctions::random(x_min_, x_max_),
										evol::EvolFunctions::random(y_min_, y_max_),
										0.0 });
}

} // namespace model
