#pragma once
#include <list>
#include <map>

#include "atomic.h"
#include "ModelOptions.h"
#include "ModelObserver.h"
#include "PopulationSnapshot.h"
#include "Evolution.h"
#include "BlockingQueue.hpp"
#include "SafeQueue.hpp"

namespace model {

class Model {
public:
	// COMMANDS
	void doStep();
	void doGeneration();
	void doRestart();
    void doCommit();
	void doExit();
	void doImmidiateExit();
	
	// SETUP
	void setFitnessFunction(const std::string& formula);	
	void setInitializationOptions(const common::InitializationOptions& options);
	void setReproductionOptions(const common::ReproductionOptions& options);
	void setMutationOptions(const common::MutationOptions& options);
	void setCrossOverOptions(const common::CrossOverOptions& options);
	void setRangeOptions(const common::RangeAlignmentOptions& options);
	void setSelectionType(const common::SelectionOptions& options);	
	void setPopulationSize(const unsigned int& size);
	void setGoalValue(const double& goal);

	// GETTERS
	common::PopulationSnapshot getPopulationSnapshot();
	unsigned int getGenerationId();

	// OBSERVERS MANAGMENT
	void addObserver(common::ModelObserver* observer);
	void removeObserver(common::ModelObserver* observer);

	void operator()();

private:
	typedef std::function<void(common::ModelObserver*)> Notification;
	typedef std::function<void()> CommandCall;
	struct ObservedCommand {
		ObservedCommand(CommandCall, Notification);
		CommandCall command;
		Notification callback;
	};

	// Every policy covers itselfs and following
	struct ApplyPolicy {
		enum policy { INSTANT = 0, STEP, GENERATION, INITIALIZATION, POLICY_SIZE };
	};
	struct Command {
        enum cmd { COMMIT, STEP, GENERATION, RESTART, EXIT };
	};

	void invokeReadySetters();
	void invokeAllFromSafeQueue(utils::SafeQueue<ObservedCommand>& queue);
	void invokeCommand(Command::cmd command);
	ApplyPolicy::policy currentApplyPolicy();

	void NotifyAll(Notification notification);

	Evolution evol_;
	std::list<common::ModelObserver*> observers_; // FIXME Thread safty
	common::BlockingQueue<Command::cmd> commands_;
	utils::SafeQueue<ObservedCommand> evol_commands_[ApplyPolicy::POLICY_SIZE];
	bool exit_;

	utils::atomic<common::PopulationSnapshot> current_snapshot_;
};

} // namespace model
