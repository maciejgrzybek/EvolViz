#pragma once
#include "ModelOptions.h"
#include "PopulationSnapshot.h"

namespace model {

class Model
{
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
	PopulationSnapshot getPopulationSnapshot();
	std::string getCurrentFormula();

	void operator()();

private:
	enum ApplyPolicy { INSTANT, STEP, GENERATION, INITIALIZATION };
};

} // namespace model