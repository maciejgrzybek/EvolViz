#include "Controller.h"


Controller::Controller(std::shared_ptr<common::BlockingQueue<common::MessagePtr,
															 common::TimeoutWait<200> > > blockingQueue,
					   std::shared_ptr<Model> model)
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

void Controller::dispatchMessage(std::unique_ptr<common::Message> message)
{
	message->accept(*this);
}