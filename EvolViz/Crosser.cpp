#include "Crosser.h"
#include "EvolFunctions.hpp"

namespace model {

CrosserPtr Crosser::Factory::produce(const common::CrossOverOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Crosser::Factory::visit(const common::ConstAvgCrossOver& options) {
	last_produced_ = CrosserPtr(new ConstAvgCrosser(options.cross_over_factor, options.x_weight, options.y_weight));
}

void Crosser::Factory::visit(const common::UniversalRandomAvgCrossOver& options) {
	last_produced_ = CrosserPtr(new UniAvgCrosser(options.cross_over_factor, options.x, options.y));
}

void Crosser::Factory::visit(const common::GaussRandomAvgCrossOver& options) {
	last_produced_ = CrosserPtr(new GaussAvgCrosser(options.cross_over_factor, options.x, options.y));
}
void Crosser::Factory::visit(const common::UniversalRandomFixedCrossOver& options){
	last_produced_ = CrosserPtr(new UniFixedCrosser(options.cross_over_factor));
}

Crosser::Crosser(const double cross_over_factor)
	: cross_over_factor_(cross_over_factor) {
}
	
ConstAvgCrosser::ConstAvgCrosser(const double cross_over_factor, const double x_weight, const double y_weight)
	: Crosser(cross_over_factor), x_weight_(x_weight), y_weight_(y_weight) {
}

UniAvgCrosser::UniAvgCrosser(const double cross_over_factor, const common::UniversalRandomOptions x, const common::UniversalRandomOptions y)
	: Crosser(cross_over_factor), x_uni_(x), y_uni_(y) {
}

GaussAvgCrosser::GaussAvgCrosser(const double cross_over_factor, const common::GaussRandomOptions x, const common::GaussRandomOptions y)
	: Crosser(cross_over_factor), x_gauss_(x), y_gauss_(y) {
}

UniFixedCrosser::UniFixedCrosser(const double cross_over_factor)
	: Crosser(cross_over_factor) {
}

void ConstAvgCrosser::operator()(Population& population) const {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size())],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size())]));
}

Population::Subject ConstAvgCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	Population::Subject result = { 0.0, 0.0, 0.0 };
	return result; // FIXME implement this
}

void UniAvgCrosser::operator()(Population& population) const {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size())],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size())]));
}

Population::Subject UniAvgCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	Population::Subject result = { 0.0, 0.0, 0.0 };
	return result; // FIXME implement this
}

void GaussAvgCrosser::operator()(Population& population) const {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size())],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size())]));
}

Population::Subject GaussAvgCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	Population::Subject result = { 0.0, 0.0, 0.0 };
	return result; // FIXME implement this
}

void UniFixedCrosser::operator()(Population& population) const {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size())],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size())]));
}

Population::Subject UniFixedCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	Population::Subject result = { 0.0, 0.0, 0.0 };
	return result; // FIXME implement this
}

} // namespace model
