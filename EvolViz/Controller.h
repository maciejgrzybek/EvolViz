#pragma once

#include <memory>

#include "BlockingQueue.hpp"
#include "Message.h"

class Controller
{
public:
	Controller(std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue);
	virtual ~Controller();
	virtual void operator()();

private:
	std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue;
};

