#pragma once
#include <chrono>
#include "ModelOptions.h"

namespace model {

class Model
{
public:
	Model();
	~Model();

	void doStep();
	void doGeneration();
	void doGenerations(unsigned int generations, std::chrono::milliseconds interval = std::chrono::milliseconds(0));
	
	void setFitnessFunction(const std::string& formula);
	void setInitializationOptions(const common::InitializationOptions& options);
	void setMutationOptionsX(const common::MutationOptions& options);
	void setMutationOptionsY(const common::MutationOptions& options);
	void setCrossOverOptions(const common::CrossOverOptions& options);
	void setRangeOptions(const common::RangeAlignmentOptions& type);
	void setSelectionType(const common::SelectionType& type);	
	void setPopulationSize(const unsigned int& size);
	void setGoalValue(const double& goal);

	void operator()();
};

} // namespace model