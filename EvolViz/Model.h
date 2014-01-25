#pragma once
#include <list>
#include <map>

#include "ModelOptions.h"
#include "ModelObserver.h"
#include "PopulationSnapshot.h"
#include "Evolution.h"
#include "BlockingQueue.hpp"
#include "SafeQueue.hpp"

namespace model {

typedef std::function<void(ModelObserver*)> Notification;
struct ObservedCommand {
	std::function<void()> command;
	Notification callback;
};

class Model {
public:
	Model();
	~Model();

	// COMMANDS
	void doStep();
	void doGeneration();
	void doRestart();
	void doExit();
	void doImmidiateExit();
	
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
	unsigned int getGenerationId();

	// OBSERVERS MANAGMENT
	void addObserver(ModelObserver* observer);
	void removeObserver(ModelObserver* observer);

	void operator()();

private:
	// Every policy covers itselfs and following
	struct ApplyPolicy {
		enum policy { INSTANT = 0, STEP, GENERATION, INITIALIZATION, POLICY_SIZE };
	};
	struct Command {
		enum cmd { STEP, GENERATION, RESTART, EXIT };
	};

	void invokeReadySetters();
	void invokeAllFromSafeQueue(utils::SafeQueue<ObservedCommand>& queue);
	void invokeCommand(Command::cmd command);
	ApplyPolicy::policy currentApplyPolicy();

	void NotifyAll(Notification notification);

	Evolution evol_;
	std::list<ModelObserver*> observers_; // FIXME Thread safty
	common::BlockingQueue<Command::cmd> commands_;
	utils::SafeQueue<ObservedCommand> evol_commands_[ApplyPolicy::POLICY_SIZE];
	bool exit_;
};

} // namespace model