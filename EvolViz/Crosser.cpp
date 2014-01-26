#include "Crosser.h"
#include "EvolFunctions.hpp"

namespace model {

CrosserPtr Crosser::Factory::produce(const common::CrossOverOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Crosser::Factory::visit(const common::QualityAvgCrossOver& options) {
	last_produced_ = CrosserPtr(new QualityAvgCrosser(options.cross_over_factor));
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

void Crosser::Factory::visit(const common::QualityRandomFixedCrossOver& options) {
	last_produced_ = CrosserPtr(new QualityFixedCrosser(options.cross_over_factor));
}

void Crosser::Factory::visit(const common::UniversalRandomFixedCrossOver& options){
	last_produced_ = CrosserPtr(new UniFixedCrosser(options.cross_over_factor));
}

Crosser::Crosser(const double cross_over_factor)
	: cross_over_factor_(cross_over_factor) {
}

QualityAvgCrosser::QualityAvgCrosser(const double cross_over_factor) 
	: Crosser(cross_over_factor) {
}

ConstAvgCrosser::ConstAvgCrosser(const double cross_over_factor, const double x_weight[2], const double y_weight[2])
	: Crosser(cross_over_factor), x_weight_first_(x_weight[0]), x_weight_second_(x_weight[1]), y_weight_first_(y_weight[0]), y_weight_second_(y_weight[1]) {
}

UniAvgCrosser::UniAvgCrosser(const double cross_over_factor, const common::UniversalRandomOptions x[2], const common::UniversalRandomOptions y[2])
	: Crosser(cross_over_factor), x_uni_first_(x[0]), x_uni_second_(x[1]), y_uni_first_(y[0]), y_uni_second_(y[1]) {
}

GaussAvgCrosser::GaussAvgCrosser(const double cross_over_factor, const common::GaussRandomOptions x[2], const common::GaussRandomOptions y[2])
	: Crosser(cross_over_factor), x_gauss_first_(x[0]), x_gauss_second_(x[1]), y_gauss_first_(y[0]), y_gauss_second_(y[1]) {
}

QualityFixedCrosser::QualityFixedCrosser(const double cross_over_factor)
	: Crosser(cross_over_factor) {
}

UniFixedCrosser::UniFixedCrosser(const double cross_over_factor)
	: Crosser(cross_over_factor) {
}

void QualityAvgCrosser::operator()(Population& population) const {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size())],
		population.subjects[evol::EvolFunctions::random(0, population.subjects.size())]));
}

Population::Subject QualityAvgCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	Population::Subject result = { 0.0, 0.0, 0.0 };
	return result; // FIXME implement this
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

void QualityFixedCrosser::operator()(Population& population) const {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size())],
		population.subjects[evol::EvolFunctions::random(0, population.subjects.size())]));
}

Population::Subject QualityFixedCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
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
