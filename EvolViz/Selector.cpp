#include "Selector.h"
namespace model {

SelectorPtr Selector::Factory::produce(const common::SelectionOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Selector::Factory::visit(const common::EliteSelection& options) {
	last_produced_ = SelectorPtr(new EliteSelector());
}

void Selector::Factory::visit(const common::LoterySelection& options) {
	last_produced_ = SelectorPtr(new LoterySelector());
}
void Selector::Factory::visit(const common::TournamentSelection& options) {
	last_produced_ = SelectorPtr(new TournamentSelector());
}

void Selector::Factory::visit(const common::RouletteSelection& options) {
	last_produced_ = SelectorPtr(new RouletteSelector());
}

void EliteSelector::operator()(Population& population, unsigned int size) const {
	//FIXME implement this
};

void LoterySelector::operator()(Population& population, unsigned int size) const {
	//FIXME implement this
};

void TournamentSelector::operator()(Population& population, unsigned int size) const {
	//FIXME implement this
};

void RouletteSelector::operator()(Population& population, unsigned int size) const {
	//FIXME implement this
};

} // namespace model
