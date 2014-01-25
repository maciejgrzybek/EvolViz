#include "Initializer.h"
namespace model {

InitializerPtr Initializer::Factory::produce(const common::InitializationOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Initializer::Factory::visit(const common::PointInitialization& options) {
	last_produced_ = InitializerPtr(new PointInitializer(options.x, options.y));
}

void Initializer::Factory::visit(const common::RandomInitialization& options) {
	last_produced_ = InitializerPtr(new RandomInitializer());
}

PointInitializer::PointInitializer(const double x, const double y)
	: x_(x), y_(y) {
}

void PointInitializer::operator()(Population& population, unsigned int size) const {
	//FIXME implement this
}

void RandomInitializer::operator()(Population& population, unsigned int size) const {
	//FIXME implement this
}

} // namespace model
