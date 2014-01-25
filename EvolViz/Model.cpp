#include "Model.h"
#include "evol/EvolFunctions.hpp"

namespace model {

Model::Model() {
}

Model::~Model() {
}

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

void Model::operator()() {
	Command::cmd command;
	exit_ = false;
	while (!exit_) {		
		commands_.pop(command);
		invokeReadySetters();
		invokeCommand(command);		
	}
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