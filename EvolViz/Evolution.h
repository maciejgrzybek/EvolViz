#pragma once
#include "Population.h"
#include "Initializer.h"
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
	~Evolution();

	void doStep();
	void doGeneration();

	bool isBeforeInitialization();
	bool isBeforeGeneration();
	bool isBeforeStep();
	State state();

	void set_goal(double goal);
	void set_population_size(unsigned int size);

private:
	State state_;
	
	// Functors
	InitializerPtr initializer_;
	MutatorPtr mutator_;
	CrosserPtr crosser_;
	AlignatorPtr alignetor_;
	SelectorPtr selector_;
	FitnessFunctionerPtr fitness_function_;

	double goal_;
	unsigned int population_size_;
	Population population;
};

} // Evolution

