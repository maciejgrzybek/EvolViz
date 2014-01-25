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
						std::bind(&ModelObserver::onFitnessFunctionApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::GENERATION].push(cmd);
}

void Model::setInitializationOptions(const common::InitializationOptions& options) {
	InitializerPtr initializer = Initializer::produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_initializer, &evol_, initializer),
					    std::bind(&ModelObserver::onInitializationOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::INITIALIZATION].push(cmd);
}

void Model::setReproductionOptions(const common::ReproductionOptions& options) {
	ReproductorPtr reproductor = Reproductor::produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_reproductor, &evol_, reproductor),
						std::bind(&ModelObserver::onReproductionOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::INITIALIZATION].push(cmd);
}

void Model::setMutationOptions(const common::MutationOptions& options) {
	MutatorPtr mutator = Mutator::produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_mutator, &evol_, mutator),
						std::bind(&ModelObserver::onMutationOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setCrossOverOptions(const common::CrossOverOptions& options) {
	CrosserPtr crosser = Crosser::produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_crosser, &evol_, crosser),
						std::bind(&ModelObserver::onCrossOverOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setRangeOptions(const common::RangeAlignmentOptions& options) {
	AlignatorPtr alignator = Alignator::produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_alignator, &evol_, alignator),
						std::bind(&ModelObserver::onRangeOptionsApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setSelectionType(const common::SelectionOptions& options) {
	SelectorPtr selector = Selector::produce(options);
	ObservedCommand cmd(std::bind(&Evolution::set_selector, &evol_, selector),
						std::bind(&ModelObserver::onSelectionTypeApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setPopulationSize(const unsigned int& size) {
	ObservedCommand cmd(std::bind(&Evolution::set_population_size, &evol_, size),
						std::bind(&ModelObserver::onPopulationSizeApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

void Model::setGoalValue(const double& goal) {
	ObservedCommand cmd(std::bind(&Evolution::set_goal, &evol_, goal),
						std::bind(&ModelObserver::onPopulationSizeApplied, std::placeholders::_1));
	evol_commands_[ApplyPolicy::STEP].push(cmd);
}

common::PopulationSnapshot Model::getPopulationSnapshot() {
	return current_snapshot_.load();
}

unsigned int Model::getGenerationId() {
	return evol_.generation_id();
}

void Model::addObserver(ModelObserver* observer) {
	observers_.push_back(observer);
}

void Model::removeObserver(ModelObserver* observer) {
	observers_.remove(observer);
}

void Model::operator()() {
	Command::cmd command;
	exit_ = false;
	while (!exit_) {		
		current_snapshot_ = evol_.population();
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
			evol_.doStep();
		break;
		case Command::GENERATION:
			evol_.doGeneration();
		break;
		case Command::RESTART:
			evol_.doRestart();
		break;
		case Command::EXIT:
			exit_ = true;
		break;
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
	for (ModelObserver* observer : observers_)
		notification(observer);
}

} // namespace model