#include "Controller.h"


Controller::Controller(std::shared_ptr<BlockingQueue> blockingQueue,
					   std::shared_ptr<model::Model> model)
	: blockingQueue(blockingQueue),
	  model(model),
	  working(false)
{}

Controller::~Controller()
{}

void Controller::operator()()
{
	working = true;
	while (working)
	{
		common::MessagePtr msg;
		blockingQueue->pop(msg);
		dispatchMessage(std::move(msg));
	}
}

void Controller::asyncStop()
{
	working = false;
}

void Controller::visit(const common::StartRequestedMessage& message)
{
	// FIXME implement this
}

void Controller::visit(const common::StopRequestedMessage& message)
{
	// FIXME implement this
}

void Controller::visit(const common::FitnessFunctionChangeRequestedMessage& message)
{
	// FIXME implement this
}

void Controller::visit(const common::StateChangedMessage& message)
{
	// FIXME implement this
	// ask Model for fresh state (be aware of thread-safety!)
}

void Controller::onStateChanged()
{
	// enqueue Message for further evaluation in proper (Controller's) thread.
	common::MessagePtr msg(new common::StateChangedMessage);
	blockingQueue->push(std::move(msg));
}

void Controller::onGoalReached()
{
	// FIXME implement this
}

void Controller::onProcessingStarted()
{
	// FIXME implement this
}

void Controller::onProcessingStoped()
{
	// FIXME implement this
}

void Controller::onFitnessFunctionApplied()
{
	// FIXME implement this
}

void Controller::onInitializationOptionsApplied()
{
	// FIXME implement this
}

void Controller::onReproductionOptionsApplied()
{
	// FIXME implement this
}

void Controller::onMutationOptionsApplied()
{
	// FIXME implement this
}

void Controller::onCrossOverOptionsApplied()
{
	// FIXME implement this
}

void Controller::onRangeOptionsApplied()
{
	// FIXME implement this
}

void Controller::onSelectionTypeApplied()
{
	// FIXME implement this
}

void Controller::onPopulationSizeApplied()
{
	// FIXME implement this
}

void Controller::onGoalValueApplied()
{
	// FIXME implement this
}

void Controller::dispatchMessage(std::unique_ptr<common::Message> message)
{
	message->accept(*this);
}