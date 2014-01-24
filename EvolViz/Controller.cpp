#include "Controller.h"


Controller::Controller(std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue,
					   std::shared_ptr<Model> model)
	: blockingQueue(blockingQueue),
	  model(model)
{}

Controller::~Controller()
{}

void Controller::operator()()
{
	// FIXME implement this
	// pick message from blockingQueue and execute appropriate command according to message
}

void Controller::visit(const common::StartRequestedMessage& message)
{
	// FIXME implement this
}

void Controller::visit(const common::StopRequestedMessage& message)
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