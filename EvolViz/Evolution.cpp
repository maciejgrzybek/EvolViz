#include "Evolution.h"
#include <cassert>

namespace model {

void Evolution::doStep() {
	switch (state_) {
		case BEFORE_INITIALIZATION:
			generation_id_ = 0;
			population_.subjects.clear();
			(*initializer_)(population_, population_size_);
			state_ = BEFORE_REPRODUCTION;
		break;
		case BEFORE_REPRODUCTION:
			if (isGoalReached())
				return;
			generation_id_++;
			(*reproductor_)(population_);			
			state_ = BEFORE_MUTATION;
		break;
		case BEFORE_MUTATION:
			(*mutator_)(population_);
			state_ = BEFORE_CROSSOVER;
		break;
		case BEFORE_CROSSOVER:
			(*crosser_)(population_);
			state_ = BEFORE_SELECTION;
		break;
		case BEFORE_SELECTION:
			(*selector_)(population_, population_size_);
			updateBest();
			state_ = BEFORE_REPRODUCTION;
		break;
		default: assert(false);
	}
	(*fitness_function_)(population_);
}

void Evolution::doGeneration() {
	do {
		doStep();
	} while (!isBeforeGeneration());
}

void Evolution::doRestart() {
	state_ = BEFORE_INITIALIZATION;
}

bool Evolution::isBeforeInitialization() {
	return state_ == BEFORE_INITIALIZATION;
}

bool Evolution::isBeforeGeneration() {
	return state_ == BEFORE_GENERATION ||
		   isBeforeInitialization();
}

bool Evolution::isBeforeStep() {
	return true;
}

Evolution::State Evolution::state() {
	return state_;
}

Population Evolution::population() {
	return population_;
}

unsigned int Evolution::generation_id() {
	return generation_id_.load();
}

void Evolution::set_goal(double goal) {
	goal_ = goal;
}

void Evolution::set_population_size(unsigned int size) {
	population_size_ = size;
}

void Evolution::set_initializer(InitializerPtr initializer) {
	initializer_ = initializer;
}

void Evolution::set_reproductor(ReproductorPtr reproductor) {
	reproductor_ = reproductor;
}

void Evolution::set_mutator(MutatorPtr mutator) {
	mutator_ = mutator;
}
void Evolution::set_crosser(CrosserPtr crosser) {
	crosser_ = crosser;
}

void Evolution::set_alignator(AlignatorPtr alignator) {
	alignator_ = alignator;
}

void Evolution::set_selector(SelectorPtr selector) {
	selector_ = selector;
}

void Evolution::set_fitness_functioner(FitnessFunctionerPtr fitness_funtion) {
	fitness_function_ = fitness_funtion;
	(*fitness_function_)(population_);
	updateBest();
}

} // namespace model