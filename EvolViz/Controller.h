#pragma once

#include <memory>

#include "BlockingQueue.hpp"
#include "Message.h"
#include "Model.h""
#include "ModelObserver.h"

class Controller : public ModelObserver,
				   public common::MessageVisitor
{
public:
	Controller(std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue, std::shared_ptr<Model> model);
	virtual ~Controller();
	virtual void operator()();

	virtual void visit(const common::StartRequestedMessage& message);
	virtual void visit(const common::StopRequestedMessage& message);
	virtual void visit(const common::StateChangedMessage& message);

	virtual void onStateChanged();

private:
	std::shared_ptr<common::BlockingQueue<common::MessagePtr> > blockingQueue;
	std::shared_ptr<Model> model;
};

