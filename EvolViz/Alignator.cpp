#include "Alignator.h"
namespace model {

AlignatorPtr Alignator::Factory::produce(const common::RangeAlignmentOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Alignator::Factory::visit(const common::RollingRangeAlignment& options) {
	last_produced_ = AlignatorPtr(new RollingAlignator(options.x_min, options.x_max, options.y_min, options.y_max));
}

void Alignator::Factory::visit(const common::MirroringRangeAlignment& options) {
	last_produced_ = AlignatorPtr(new MirroringAlignator(options.x_min, options.x_max, options.y_min, options.y_max));
}

void Alignator::Factory::visit(const common::UniversalRandomReinitializationAlignment& options) {
	last_produced_ = AlignatorPtr(new ReinitializationAlignator(options.x_min, options.x_max, options.y_min, options.y_max));
}

Alignator::Alignator(double x_min, double x_max, double y_min, double y_max)
	: x_min_(x_min), x_max_(x_max), y_min_(y_min), y_max_(y_max) {
}

RollingAlignator::RollingAlignator(double x_min, double x_max, double y_min, double y_max)
	: Alignator(x_min, x_max, y_min, y_max) {
}

MirroringAlignator::MirroringAlignator(double x_min, double x_max, double y_min, double y_max)
	: Alignator(x_min, x_max, y_min, y_max) {
}

ReinitializationAlignator::ReinitializationAlignator(double x_min, double x_max, double y_min, double y_max)
	: Alignator(x_min, x_max, y_min, y_max) {
}

void RollingAlignator::operator()(Population& population) const {
	// FIXME implement this
}

void MirroringAlignator::operator()(Population& population) const {
	// FIXME implement this
}

void ReinitializationAlignator::operator()(Population& population) const {
	// FIXME implement this
}

} // namespace model
