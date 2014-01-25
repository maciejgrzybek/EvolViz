#include "Mutator.h"
namespace model {

MutatorPtr Mutator::Factory::produce(const common::MutationOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Mutator::Factory::visit(const common::UniversalRandomMutation& options) {
	last_produced_ = MutatorPtr(new UniRandMutator(options.mutation_rate, options.x, options.y));
}

void Mutator::Factory::visit(const common::GaussRandomMutation& options) {
	last_produced_ = MutatorPtr(new GaussRandMutator(options.mutation_rate, options.x, options.y));
}

void Mutator::Factory::visit(const common::ConstMutation& options) {
	last_produced_ = MutatorPtr(new ConstMutator(options.mutation_rate, options.x, options.y));
}

Mutator::Mutator(const double mutation_rate)
	: mutation_rate_(mutation_rate) {
}

UniRandMutator::UniRandMutator(const double mutation_rate, const common::UniversalRandomOptions x, const common::UniversalRandomOptions y)
	: Mutator(mutation_rate), x_uni_(x), y_uni_(y) {
}

GaussRandMutator::GaussRandMutator(const double mutation_rate, const common::GaussRandomOptions x, const common::GaussRandomOptions y)
	: Mutator(mutation_rate), x_gauss_(x), y_gauss_(y) {
}

ConstMutator::ConstMutator(const double mutation_rate, const double x, const double y)
	: Mutator(mutation_rate), x_const_(x), y_const_(y) {
}

void UniRandMutator::operator()(Population& population) const {
	//FIXME implement this
}

void GaussRandMutator::operator()(Population& population) const {
	//FIXME implement this
}

void ConstMutator::operator()(Population& population) const {
	//FIXME implement this
}

} // namespace model
