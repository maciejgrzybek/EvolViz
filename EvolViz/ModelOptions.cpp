#include "ModelOptions.h"

#define IMPLEMENT_VISITABLE(type, visitor_type) \
void type::accept(visitor_type& visitor) const {\
	visitor.visit(*this); \
}

namespace common {
// So much 80', wow
// So define
// wow, so preprocessing
// so enterprice, wow
IMPLEMENT_VISITABLE(PointInitialization, InitializationOptionsVisitor)
IMPLEMENT_VISITABLE(RandomInitialization, InitializationOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomMutation, MutationOptionsVisitor)
IMPLEMENT_VISITABLE(GaussRandomMutation, MutationOptionsVisitor)
IMPLEMENT_VISITABLE(ConstMutation, MutationOptionsVisitor)
IMPLEMENT_VISITABLE(QualityAvgCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(ConstAvgCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomAvgCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(GaussRandomAvgCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(QualityRandomFixedCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomFixedCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(RollingRangeAlignment, RangeAlignmentOptionsVisitor)
IMPLEMENT_VISITABLE(MirroringRangeAlignment, RangeAlignmentOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomReinitializationAlignment, RangeAlignmentOptionsVisitor)
IMPLEMENT_VISITABLE(EliteSelection, SelectionOptionsVisitor)
IMPLEMENT_VISITABLE(LoterySelection, SelectionOptionsVisitor)
IMPLEMENT_VISITABLE(TournamentSelection, SelectionOptionsVisitor)
IMPLEMENT_VISITABLE(RouletteSelection, SelectionOptionsVisitor)

UniversalRandomOptions::UniversalRandomOptions()
	: UniversalRandomOptions(0.0, 0.0) {
}

UniversalRandomOptions::UniversalRandomOptions(double min, double max) 
	: min(min), max(max) {
}

GaussRandomOptions::GaussRandomOptions()
	: GaussRandomOptions(0.0, 0.0) {
}

GaussRandomOptions::GaussRandomOptions(double expected, double variation) 
	: expected(expected), variation(variation) {
}

PointInitialization::PointInitialization(double x, double y) 
	: x(x), y(y) {
}

RandomInitialization::RandomInitialization(double x_min, double x_max, double y_min, double y_max) 
	: x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max) {
}

MutationOptions::MutationOptions(double mutation_rate) 
	: mutation_rate(mutation_rate) {
}

UniversalRandomMutation::UniversalRandomMutation(double mutation_rate, UniversalRandomOptions x, UniversalRandomOptions y)
	: MutationOptions(mutation_rate), x(x), y(y) {
}

GaussRandomMutation::GaussRandomMutation(double mutation_rate, GaussRandomOptions x, GaussRandomOptions y) 
	: MutationOptions(mutation_rate), x(x), y(y) {
}

ConstMutation::ConstMutation(double mutation_rate, double x, double y) 
	: MutationOptions(mutation_rate), x(x), y(y) {
}

ReproductionOptions::ReproductionOptions(double rate) 
	: rate(rate) {
}

CrossOverOptions::CrossOverOptions(double cross_over_factor)
	: cross_over_factor(cross_over_factor) {
}

QualityAvgCrossOver::QualityAvgCrossOver(double cross_over_factor, double normalizator) 
	: CrossOverOptions(cross_over_factor), normalizator(normalizator) {
}

ConstAvgCrossOver::ConstAvgCrossOver(double cross_over_factor, double x_weight[2], double y_weight[2]) 
	: CrossOverOptions(cross_over_factor) {
	this->x_weight[0] = x_weight[0];
	this->x_weight[1] = x_weight[1];
	this->y_weight[0] = y_weight[0];
	this->y_weight[1] = y_weight[1];
}

UniversalRandomAvgCrossOver::UniversalRandomAvgCrossOver(double cross_over_factor, UniversalRandomOptions x[2], UniversalRandomOptions y[2]) 
	: CrossOverOptions(cross_over_factor) {
	this->x[0] = x[0];
	this->x[1] = x[1];
	this->y[0] = y[0];
	this->y[1] = y[1];
}

GaussRandomAvgCrossOver::GaussRandomAvgCrossOver(double cross_over_factor, GaussRandomOptions x[2], GaussRandomOptions y[2])
	: CrossOverOptions(cross_over_factor) {
	this->x[0] = x[0];
	this->x[1] = x[1];
	this->y[0] = y[0];
	this->y[1] = y[1];
}

QualityRandomFixedCrossOver::QualityRandomFixedCrossOver(double cross_over_factor, double normalizator)
	: CrossOverOptions(cross_over_factor), normalizator(normalizator) {
}

UniversalRandomFixedCrossOver::UniversalRandomFixedCrossOver(double cross_over_factor)
	: CrossOverOptions(cross_over_factor) {
}

RangeAlignmentOptions::RangeAlignmentOptions(double x_min, double x_max, double y_min, double y_max)
	: x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max) {
}

RollingRangeAlignment::RollingRangeAlignment(double x_min, double x_max, double y_min, double y_max) 
	: RangeAlignmentOptions(x_min, x_max, y_min, y_max) {
}

MirroringRangeAlignment::MirroringRangeAlignment(double x_min, double x_max, double y_min, double y_max)
	: RangeAlignmentOptions(x_min, x_max, y_min, y_max) {
}

UniversalRandomReinitializationAlignment::UniversalRandomReinitializationAlignment(double x_min, double x_max, double y_min, double y_max)
	: RangeAlignmentOptions(x_min, x_max, y_min, y_max) {
}

RouletteSelection::RouletteSelection(double normalizator)
    : normalizator(normalizator) {
}

} // namespace model
