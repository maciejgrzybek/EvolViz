#include "Selector.h"
#include <algorithm>
#include <list>
#include <cassert>
#include <vector>
#include "EvolFunctions.hpp"

namespace model {

SelectorPtr Selector::Factory::produce(const common::SelectionOptions& options) {
	options.accept(*this);
	return last_produced_;
}

void Selector::Factory::visit(const common::EliteSelection& /*options*/) {
	last_produced_ = SelectorPtr(new EliteSelector());
}

void Selector::Factory::visit(const common::LoterySelection& /*options*/) {
	last_produced_ = SelectorPtr(new LoterySelector());
}
void Selector::Factory::visit(const common::TournamentSelection& /*options*/) {
	last_produced_ = SelectorPtr(new TournamentSelector());
}

void Selector::Factory::visit(const common::RouletteSelection& /*options*/) {
	last_produced_ = SelectorPtr(new RouletteSelector());
}

void EliteSelector::operator()(Population& population, unsigned int size) const {
	if (population.subjects.size() < size)
        return;
	std::sort(population.subjects.begin(), population.subjects.end());
    population.subjects.erase(population.subjects.begin() + size, population.subjects.end());
}

void LoterySelector::operator()(Population& population, unsigned int size) const {
	if (population.subjects.size() < size)
		return
	std::sort(population.subjects.begin(), population.subjects.end());
	unsigned int tickets_count = ((population.subjects.size() + 1) / 2)*population.subjects.size();
	std::list<unsigned int> selected;
	while (selected.size() < size) {
		unsigned int win_ticket = evol::EvolFunctions::random(1, tickets_count);		
		unsigned int winner = population.subjects.size() - 1;
		unsigned int current = population.subjects.size() - 1;
        for (int i = current; current < win_ticket; --i, current += (i+1))
			winner = i;
		winner = population.subjects.size() - winner;
		assert(winner < population.subjects.size());

		selected.push_back(winner);
	}
	std::vector<Population::Subject> new_subjects;
	for (unsigned int selected_element : selected)
		new_subjects.push_back(population.subjects[selected_element]);
	std::swap(population.subjects, new_subjects);
}

void TournamentSelector::operator()(Population& population, unsigned int size) const {
	if (population.subjects.size() < size)
		return
	std::sort(population.subjects.begin(), population.subjects.end());
	while (population.subjects.size() > size) {
        int fighters[] = { evol::EvolFunctions::random(0, population.subjects.size() - 1),
                           evol::EvolFunctions::random(0, population.subjects.size() - 1) };
		if (fighters[0] == fighters[1])
			continue;
		double fighter_power[] = { population.subjects[fighters[0]].value, population.subjects[fighters[1]].value };
		double fighters_power = fighter_power[0] + fighter_power[1];
		unsigned int looser = fighters[1];
		if (evol::EvolFunctions::random(0.0, fighters_power) > fighter_power[0])
			looser = fighters[0];
		population.subjects.erase(population.subjects.begin() + looser);
	}
}

void RouletteSelector::operator()(Population& population, unsigned int size) const {
	if (population.subjects.size() < size)
		return
	std::sort(population.subjects.begin(), population.subjects.end());
	
	double pool = 0.0;
	for (Population::Subject& subject : population.subjects)
		pool += subject.value;

	std::list<unsigned int> selected;
	while (selected.size() < size) {
		double win_value = evol::EvolFunctions::random(0.0, pool);
		unsigned int winner = 0;
		double current = 0.0;
		for (Population::Subject& subject : population.subjects) {
			current += subject.value;
            if (current >= win_value)
				break;
			++winner;
		}
		assert(winner < population.subjects.size());

		selected.push_back(winner);
	}

	std::vector<Population::Subject> new_subjects;
	for (unsigned int selected_element : selected)
		new_subjects.push_back(population.subjects[selected_element]);
	std::swap(population.subjects, new_subjects);
}

} // namespace model
