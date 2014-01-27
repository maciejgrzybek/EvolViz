#include "Crosser.h"
#include "EvolFunctions.hpp"
#include <algorithm>

namespace model {

CrosserPtr Crosser::Factory::produce(const common::CrossOverOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Crosser::Factory::visit(const common::QualityAvgCrossOver& options) {
	last_produced_ = CrosserPtr(new QualityAvgCrosser(options.cross_over_factor, options.normalizator));
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
	last_produced_ = CrosserPtr(new QualityFixedCrosser(options.cross_over_factor, options.normalizator));
}

void Crosser::Factory::visit(const common::UniversalRandomFixedCrossOver& options){
	last_produced_ = CrosserPtr(new UniFixedCrosser(options.cross_over_factor));
}

Crosser::Crosser(const double cross_over_factor)
	: cross_over_factor_(cross_over_factor) {
}

QualityAvgCrosser::QualityAvgCrosser(const double cross_over_factor, const double normalizator)
	: Crosser(cross_over_factor), normalizator_(normalizator) {
}

ConstAvgCrosser::ConstAvgCrosser(const double cross_over_factor, const double x_weight[2], const double y_weight[2])
    : Crosser(cross_over_factor), x_weight_first_(x_weight[0]), y_weight_first_(y_weight[0]), x_weight_second_(x_weight[1]), y_weight_second_(y_weight[1]) {
}

UniAvgCrosser::UniAvgCrosser(const double cross_over_factor, const common::UniversalRandomOptions x[2], const common::UniversalRandomOptions y[2])
    : Crosser(cross_over_factor), x_uni_first_(x[0]), y_uni_first_(y[0]), x_uni_second_(x[1]), y_uni_second_(y[1]) {
}

GaussAvgCrosser::GaussAvgCrosser(const double cross_over_factor, const common::GaussRandomOptions x[2], const common::GaussRandomOptions y[2])
    : Crosser(cross_over_factor), x_gauss_first_(x[0]), y_gauss_first_(y[0]), x_gauss_second_(x[1]), y_gauss_second_(y[1]) {
}

QualityFixedCrosser::QualityFixedCrosser(const double cross_over_factor, const double normalizator)
	: Crosser(cross_over_factor), normalizator_(normalizator) {
}

UniFixedCrosser::UniFixedCrosser(const double cross_over_factor)
	: Crosser(cross_over_factor) {
}

void QualityAvgCrosser::operator()(Population& population) {
	added_subjects_.clear();
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)],
			  		  population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)]);

	// Quality of added elements is unknown so we cannot use it in further crossing
	population.subjects.insert(population.subjects.end(), added_subjects_.begin(), added_subjects_.end());
}

void QualityAvgCrosser::crossSubjects(Population::Subject subject_one, Population::Subject subject_two) {
	const double normalizator = std::min(subject_one.value, std::min(subject_two.value, normalizator_));
	const double nv[] = { subject_one.value - normalizator, subject_one.value - normalizator };

	const double pool = nv[0] + nv[1];
	const double pc_first = nv[0] / pool;
	const double pc_second = nv[1] / pool;
	const double new_x = subject_one.x * pc_first + subject_two.x * pc_second;
	const double new_y = subject_one.y * pc_first + subject_two.y * pc_second;
	const Population::Subject result = { new_x, new_y, 0.0 };
	added_subjects_.push_back(result);
}

void ConstAvgCrosser::operator()(Population& population) {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)]));
}

Population::Subject ConstAvgCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	const double pool_x = x_weight_first_ + x_weight_second_;
	const double pc_first_x = subject_one.x / pool_x;
	const double pc_second_x = subject_two.x / pool_x;
	const double pool_y = y_weight_first_ + y_weight_second_;
	const double pc_first_y = subject_one.y / pool_y;
	const double pc_second_y = subject_two.y / pool_y;
	const double new_x = subject_one.x * pc_first_x + subject_two.x * pc_second_x;
	const double new_y = subject_one.y * pc_first_y + subject_two.y * pc_second_y;
	const Population::Subject result = { new_x, new_y, 0.0 };
	return result;
}

void UniAvgCrosser::operator()(Population& population) {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)]));
}

Population::Subject UniAvgCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	const double x_weight_first = evol::EvolFunctions::random(x_uni_first_.min, x_uni_first_.max);
	const double x_weight_second = evol::EvolFunctions::random(x_uni_second_.min, x_uni_second_.max);
	const double y_weight_first = evol::EvolFunctions::random(y_uni_first_.min, y_uni_first_.max);
	const double y_weight_second = evol::EvolFunctions::random(y_uni_second_.min, y_uni_second_.max);
	const double pool_x = x_weight_first + x_weight_second;
	const double pc_first_x = subject_one.x / pool_x;
	const double pc_second_x = subject_two.x / pool_x;
	const double pool_y = y_weight_first + y_weight_second;
	const double pc_first_y = subject_one.y / pool_y;
	const double pc_second_y = subject_two.y / pool_y;
	const double new_x = subject_one.x * pc_first_x + subject_two.x * pc_second_x;
	const double new_y = subject_one.y * pc_first_y + subject_two.y * pc_second_y;
	const Population::Subject result = { new_x, new_y, 0.0 };
	return result;
}

void GaussAvgCrosser::operator()(Population& population) {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)]));
}

Population::Subject GaussAvgCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	const double x_weight_first = evol::EvolFunctions::gaussRandom(x_gauss_first_.expected, x_gauss_first_.variation);	
	const double y_weight_first = evol::EvolFunctions::gaussRandom(y_gauss_first_.expected, y_gauss_first_.variation);
    const double x_weight_second = evol::EvolFunctions::gaussRandom(x_gauss_second_.expected, x_gauss_second_.variation);
	const double y_weight_second = evol::EvolFunctions::gaussRandom(y_gauss_second_.expected, y_gauss_second_.variation);
	const double pool_x = x_weight_first + x_weight_second;
	const double pc_first_x = subject_one.x / pool_x;
	const double pc_second_x = subject_two.x / pool_x;
	const double pool_y = y_weight_first + y_weight_second;
	const double pc_first_y = subject_one.y / pool_y;
	const double pc_second_y = subject_two.y / pool_y;
	const double new_x = subject_one.x * pc_first_x + subject_two.x * pc_second_x;
	const double new_y = subject_one.y * pc_first_y + subject_two.y * pc_second_y;
	const Population::Subject result = { new_x, new_y, 0.0 };
	return result;
}

void QualityFixedCrosser::operator()(Population& population) {
	added_subjects_.clear();
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)],
					  population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)]);

	// Quality of added elements is unknown so we cannot use it in further crossing
	population.subjects.insert(population.subjects.end(), added_subjects_.begin(), added_subjects_.end());
}

void QualityFixedCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) {
	const double normalizator = std::min(subject_one.value, std::min(subject_two.value, normalizator_));
	const double nv[] = { subject_one.value - normalizator, subject_one.value - normalizator };

	const double pool = nv[0] + nv[1];
	const double pc_first = nv[0] / pool;
	const double new_x = evol::EvolFunctions::random() < pc_first ? subject_one.x : subject_two.x;
	const double new_y = evol::EvolFunctions::random() < pc_first ? subject_one.y : subject_two.y;
	const Population::Subject result = { new_x, new_y, 0.0 };
	added_subjects_.push_back(result);
}


void UniFixedCrosser::operator()(Population& population) {
	unsigned int cross = static_cast<unsigned int>(round(static_cast<double>(population.subjects.size()) * cross_over_factor_));
	while (cross--)
		population.subjects.push_back(crossSubjects(population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)],
													population.subjects[evol::EvolFunctions::random(0, population.subjects.size() - 1)]));
}

Population::Subject UniFixedCrosser::crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const {
	const double chance_first_x = evol::EvolFunctions::random();
	const double chance_first_y = evol::EvolFunctions::random();

	const double new_x = evol::EvolFunctions::random() < chance_first_x ? subject_one.x : subject_two.x;
	const double new_y = evol::EvolFunctions::random() < chance_first_y ? subject_one.y : subject_two.y;
	const Population::Subject result = { new_x, new_y, 0.0 };
	return result;
}

} // namespace model
