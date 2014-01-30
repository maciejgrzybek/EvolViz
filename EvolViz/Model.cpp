#include "Model.h"
#include <functional>

namespace model {

void Model::doStep() {
	commands_.push(Command::STEP);
}
void Model::doGeneration() {
	commands_.push(Command::GENERATION);
}
void Model::doRestart() {
	commands_.push(Command::RESTART);
}
void Model::doCommit() {
    commands_.push(Command::COMMIT);
}
void Model::doExit() {
	commands_.push(Command::EXIT);
}
void Model::doImmidiateExit() {
	exit_ = true;
	commands_.push(Command::EXIT);
}

void Model::setFitnessFunction(const std::string& formula) {
	FitnessFunctionerPtr ff = FitnessFunctioner::produce(formula);
	ObservedCommand cmd(std::bind(&Evolution::set_fitness_functioner, &evol_, ff),
                        std::bind(&common::ModelObserver::onFitnessFunctionApplied, std::placeholders::_1, formula));
	evol_commands_[ApplyPolicy::GENERATION].push(cmd);
}

void Model::setInitializationOptions(const common::InitializationOptions& options) {
	InitializerPtr initializer = Initializer::Factory().produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_initializer, &evol_, initializer),
						std::bind(&common::ModelObserver::onInitializationOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::INITIALIZATION].push(cmd);
}

void Model::setReproductionOptions(const common::ReproductionOptions& options) {
	ReproductorPtr reproductor = Reproductor::produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_reproductor, &evol_, reproductor),
						std::bind(&common::ModelObserver::onReproductionOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::INITIALIZATION].push(cmd);
}

void Model::setMutationOptions(const common::MutationOptions& options) {
	MutatorPtr mutator = Mutator::Factory().produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_mutator, &evol_, mutator),
						std::bind(&common::ModelObserver::onMutationOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setCrossOverOptions(const common::CrossOverOptions& options) {
	CrosserPtr crosser = Crosser::Factory().produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_crosser, &evol_, crosser),
						std::bind(&common::ModelObserver::onCrossOverOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setRangeOptions(const common::RangeAlignmentOptions& options) {
	AlignatorPtr alignator = Alignator::Factory().produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_alignator, &evol_, alignator),
						std::bind(&common::ModelObserver::onRangeOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setSelectionType(const common::SelectionOptions& options) {
	SelectorPtr selector = Selector::Factory().produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_selector, &evol_, selector),
						std::bind(&common::ModelObserver::onSelectionTypeApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setPopulationSize(const unsigned int& size) {
	ObservedCommand cmd(std::bind(&Evolution::set_population_size, &evol_, size),
						std::bind(&common::ModelObserver::onPopulationSizeApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setGoalValue(const double& goal) {
	ObservedCommand cmd(std::bind(&Evolution::set_goal, &evol_, goal),
						std::bind(&common::ModelObserver::onGoalValueApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

common::PopulationSnapshot Model::getPopulationSnapshot() {
	return current_snapshot_.load();
}

unsigned int Model::getGenerationId() {
	return evol_.generation_id();
}

void Model::addObserver(common::ModelObserver* observer) {
	observers_.push_back(observer);
}

void Model::removeObserver(common::ModelObserver* observer) {
	observers_.remove(observer);
}

void Model::operator()() {
	Command::cmd command;
	exit_ = false;

	current_snapshot_.store(evol_.population());
	while (!exit_) {		
		commands_.pop(command);
		invokeReadySetters();		
		invokeCommand(command);
	}
}

Model::ObservedCommand::ObservedCommand(CommandCall command, Notification notification)
	: command(command), callback(notification) {
}

void Model::invokeReadySetters() {
	for (int i = currentApplyPolicy(); i >= 0; --i)
		invokeAllFromSafeQueue(evol_commands_[i]);
}

void Model::invokeAllFromSafeQueue(utils::SafeQueue<ObservedCommand>& queue) {
	while (!queue.empty()) {
		queue.front().command();
		NotifyAll(queue.front().callback);
		queue.pop();
	}
}

void Model::invokeCommand(Command::cmd command) {
	switch (command) {
		case Command::STEP:			
		case Command::GENERATION:            
            NotifyAll(std::bind(&common::ModelObserver::onProcessingStarted, std::placeholders::_1));
            if (command == Command::STEP)
                evol_.doStep();
            else
                evol_.doGeneration();
            NotifyAll(std::bind(&common::ModelObserver::onProcessingStoped, std::placeholders::_1));

            current_snapshot_.store(evol_.population());
            NotifyAll(std::bind(&common::ModelObserver::onStateChanged, std::placeholders::_1));

            if (evol_.isGoalReached())
                NotifyAll(std::bind(&common::ModelObserver::onGoalReached, std::placeholders::_1));
		break;
		case Command::RESTART:        
			evol_.doRestart();
        break;
        case Command::COMMIT:
            // NoOperation, it's just about invoking setters.
        break;
		case Command::EXIT:
			exit_ = true;
		break;        
        default: assert(false);
	}
}

Model::ApplyPolicy::policy Model::currentApplyPolicy() {
	if (evol_.isBeforeInitialization())
		return ApplyPolicy::INITIALIZATION;
	if (evol_.isBeforeGeneration())
		return ApplyPolicy::GENERATION;
	if (evol_.isBeforeStep())
		return ApplyPolicy::STEP;
	return ApplyPolicy::INSTANT;
}

void Model::NotifyAll(Notification notification) {
	for (common::ModelObserver* observer : observers_)
		notification(observer);
}

} // namespace model
