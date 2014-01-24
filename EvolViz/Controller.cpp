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