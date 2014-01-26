#pragma once

#include <atomic>
#include <memory>

#include "BlockingQueue.hpp"
#include "Message.h"
#include "Model.h"
#include "ModelObserver.h"

class Controller : public common::ModelObserver,
				   public common::MessageVisitor
{
public:
	Controller(std::shared_ptr<common::BlockingQueue<common::MessagePtr,
												     common::TimeoutWait<200> > > blockingQueue,
			   std::shared_ptr<model::Model> model);
	virtual ~Controller();
	virtual void operator()();

	virtual void asyncStop();

	// view events
	virtual void visit(const common::StartRequestedMessage& message);
	virtual void visit(const common::StopRequestedMessage& message);
	virtual void visit(const common::FitnessFunctionChangeRequestedMessage& message);

	// model events
	virtual void visit(const common::StateChangedMessage& message);

	virtual void onStateChanged();

private:
	void dispatchMessage(std::unique_ptr<common::Message> message);

	std::shared_ptr<common::BlockingQueue<common::MessagePtr, common::TimeoutWait<200> > > blockingQueue; // timeout set to allow quiting controller when no messages available
	std::shared_ptr<model::Model> model;
	std::atomic<bool> working;
};

