#pragma once

#include <memory>

#include "BlockingQueue.hpp"
#include "Message.h"
#include "ModelObserver.h"

class Controller : public ModelObserver
{
public:
	Controller(std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue);
	virtual ~Controller();
	virtual void operator()();

	virtual void onStateChanged();

private:
	std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue;
};

