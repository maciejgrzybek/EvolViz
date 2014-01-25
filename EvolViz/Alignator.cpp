#include "Alignator.h"
#include "EvolFunctions.hpp"

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

bool Alignator::isBelowXRange(const Population::Subject& subject) const {
	return subject.x < x_min_;
}

bool Alignator::isOverXRange(const Population::Subject& subject) const {
	return subject.x > x_max_;
}

bool Alignator::isBelowYRange(const Population::Subject& subject) const {
	return subject.y < y_min_;
}

bool Alignator::isOverYRange(const Population::Subject& subject) const {
	return subject.y > y_max_;
}

bool Alignator::isInRangeX(const Population::Subject& subject) const {
	return !(isBelowXRange(subject) || isOverXRange(subject));
}

bool Alignator::isInRangeY(const Population::Subject& subject) const {
	return !(isBelowYRange(subject) || isOverYRange(subject));
}

double Alignator::range_width_x() const {
	return x_max_ - x_min_;
}

double Alignator::range_width_y() const {
	return y_max_ - y_min_;
}

double Alignator::overflow_x(const Population::Subject& subject) const {
	if (isBelowXRange(subject))
		return x_min_ - subject.x;
	if (isOverXRange(subject))
		return subject.x - x_max_;
	return 0.0;
}

double Alignator::overflow_y(const Population::Subject& subject) const {
	if (isBelowYRange(subject))
		return y_min_ - subject.y;
	if (isOverYRange(subject))
		return subject.y - y_max_;
	return 0.0;
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
	for (Population::Subject& subject : population.subjects)
		alignSubject(subject);
}

void RollingAlignator::alignSubject(Population::Subject& subject) const {
	while (!isInRangeX(subject)) {
		if (isBelowXRange(subject))
			subject.x = x_max_ - overflow_x(subject);
		if (isOverXRange(subject))
			subject.x = x_min_ + overflow_x(subject);	
	}
	while (!isInRangeY(subject)) {
		if (isBelowYRange(subject))
			subject.y = y_max_ - overflow_y(subject);
		if (isOverYRange(subject))
			subject.y = y_min_ + overflow_y(subject);
	}
}

void MirroringAlignator::operator()(Population& population) const {
	for (Population::Subject& subject : population.subjects)
		alignSubject(subject);
}

void MirroringAlignator::alignSubject(Population::Subject& subject) const {
	while (!isInRangeX(subject)) {
		if (isBelowXRange(subject))
			subject.x = x_min_ + overflow_x(subject);
		if (isOverXRange(subject))
			subject.x = x_max_ - overflow_x(subject);
	}
	while (!isInRangeY(subject)) {
		if (isBelowYRange(subject))
			subject.y = y_min_ + overflow_y(subject);
		if (isOverYRange(subject))
			subject.y = y_max_ - overflow_y(subject);
	}
}

void ReinitializationAlignator::operator()(Population& population) const {
	for (Population::Subject& subject : population.subjects)
		alignSubject(subject);
}

void ReinitializationAlignator::alignSubject(Population::Subject& subject) const {
	if (!isInRangeX(subject) || !isInRangeY(subject)) {
		subject.x = evol::EvolFunctions::random(x_min_, x_max_);
		subject.y = evol::EvolFunctions::random(y_min_, y_max_);
	}
}

} // namespace model
