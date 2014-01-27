#pragma once
#include <atomic>

#include "Population.h"
#include "Initializer.h"
#include "Reproductor.h"
#include "Mutator.h"
#include "Crosser.h"
#include "Alignator.h"
#include "Selector.h"
#include "FitnessFunctioner.h"

namespace model {

class Evolution {
public:
	enum State { BEFORE_INITIALIZATION, BEFORE_GENERATION, BEFORE_REPRODUCTION = BEFORE_GENERATION, BEFORE_MUTATION, BEFORE_CROSSOVER, BEFORE_SELECTION };
    Evolution();

	void doStep();
	void doGeneration();
	void doRestart();

	bool isBeforeInitialization();
	bool isBeforeGeneration();
	bool isBeforeStep();
	bool isGoalReached();

	State state();
	Population population();
	unsigned int generation_id();

	void set_goal(double goal);
	void set_population_size(unsigned int size);
	void set_initializer(InitializerPtr initializer);
	void set_reproductor(ReproductorPtr reproductor);
	void set_mutator(MutatorPtr mutator);
	void set_crosser(CrosserPtr crosser);
	void set_alignator(AlignatorPtr alignator);
	void set_selector(SelectorPtr selector);
	void set_fitness_functioner(FitnessFunctionerPtr fitness_funtion);

private:
	void updateGoalReached();

	State state_;
	
	// Functors
	InitializerPtr initializer_;
	ReproductorPtr reproductor_;
	MutatorPtr mutator_;
	CrosserPtr crosser_;
	AlignatorPtr alignator_;
	SelectorPtr selector_;
	FitnessFunctionerPtr fitness_function_;

	double goal_;
	unsigned int population_size_;
	std::atomic<unsigned int> generation_id_;
	Population population_;
	bool goal_reached_;
};

} // Evolution

