#include "Controller.h"


Controller::Controller(std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue)
	: blockingQueue(blockingQueue)
{}

Controller::~Controller()
{}

void Controller::operator()()
{
	// FIXME implement this
	// pick message from blockingQueue and execute appropriate command according to message
}

void Controller::onStateChanged()
{
	// enqueue Message for further evaluation in proper (Controller's) thread.
	common::MessagePtr msg(new common::StateChangedMessage);
	blockingQueue->push(std::move(msg));
}