#include "Crosser.h"
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

Crosser::Crosser(double cross_over_factor) 
	: cross_over_factor_(cross_over_factor) {
}
	
ConstAvgCrosser::ConstAvgCrosser(double cross_over_factor, double x_weight, double y_weight)
	: Crosser(cross_over_factor), x_weight_(x_weight), y_weight_(y_weight) {
}

UniAvgCrosser::UniAvgCrosser(double cross_over_factor, common::UniversalRandomOptions x, common::UniversalRandomOptions y)
	: Crosser(cross_over_factor), x_uni_(x), y_uni_(y) {
}

GaussAvgCrosser::GaussAvgCrosser(double cross_over_factor, common::GaussRandomOptions x, common::GaussRandomOptions y)
	: Crosser(cross_over_factor), x_gauss_(x), y_gauss_(y) {
}

UniFixedCrosser::UniFixedCrosser(double cross_over_factor)
	: Crosser(cross_over_factor) {
}

void ConstAvgCrosser::operator()(Population& population) const {
	// FIXME implement this
}

void UniAvgCrosser::operator()(Population& population) const {
	// FIXME implement this
}

void GaussAvgCrosser::operator()(Population& population) const {
	// FIXME implement this
}

void UniFixedCrosser::operator()(Population& population) const {
	// FIXME implement this
}

} // namespace model
