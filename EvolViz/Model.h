#pragma once
#include <list>

#include "ModelOptions.h"
#include "ModelObserver.h"
#include "PopulationSnapshot.h"
#include "Evolution.h"

namespace model {

class Model {
public:
	Model();
	~Model();

	// COMMANDS
	void doStep();
	void doGeneration();
	
	// SETUP
	void setFitnessFunction(const std::string& formula);
	void setInitializationOptions(const common::InitializationOptions& options);
	void setMutationOptions(const common::MutationOptions& options);
	void setCrossOverOptions(const common::CrossOverOptions& options);
	void setRangeOptions(const common::RangeAlignmentOptions& type);
	void setSelectionType(const common::SelectionType& type);	
	void setPopulationSize(const unsigned int& size);
	void setGoalValue(const double& goal);

	// GETTERS
	common::PopulationSnapshot getPopulationSnapshot();
	std::string getCurrentFormula();

	// OBSERVERS MANAGMENT
	void addObserver(ModelObserver* observer);
	void removeObserver(ModelObserver* observer);

	void operator()();

private:
	// Every policy covers itselfs and following
	enum ApplyPolicy { INSTANT, STEP, GENERATION, INITIALIZATION };
	Evolution evol_manger_;
	std::list<ModelObserver*> observers_;
};

} // namespace model