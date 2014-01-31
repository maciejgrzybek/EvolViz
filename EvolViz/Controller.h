#pragma once

#include <memory>
#include <atomic>

#include "BlockingQueue.hpp"
#include "Message.h"
#include "Model.h"
#include "ModelObserver.h"

class View;

class Controller : public common::ModelObserver,
				   public common::MessageVisitor
{
public:
    typedef common::BlockingQueue<common::MessagePtr, common::TimeoutWait<200> // timeout set to allow quiting controller when no messages available
                                  /*common::PriorityQueueContainer<common::MessagePtr,
                                                                 common::MessagePriorityComparator>*/ > BlockingQueue;

    enum State {
        FitnessFunctionChangeRequested			= 0x0000001,
        FitnessFunctionChangeApplied			= 0x0000002,
        InitializationOptionsChangeRequested	= 0x0000004,
        InitializationOptionsChangeApplied		= 0x0000008,
        ReproductionOptionsChangeRequested		= 0x0000010,
        ReproductionOptionsChangeApplied		= 0x0000020,
        MutationOptionsChangeRequested			= 0x0000040,
        MutationOptionsChangeApplied			= 0x0000080,
        CrossOverOptionsChangeRequested			= 0x0000100,
        CrossOverOptionsChangeApplied			= 0x0000200,
        RangeOptionsChangeRequested				= 0x0000400,
        RangeOptionsChangeApplied				= 0x0000800,
        SelectionTypeChangeRequested			= 0x0001000,
        SelectionTypeChangeApplied				= 0x0002000,
        PopulationSizeChangeRequested			= 0x0004000,
        PopulationSizeChangeApplied				= 0x0008000,
        GoalValueChangeRequested				= 0x0010000,
        GoalValueChangeApplied					= 0x0020000,
        GoalReached								= 0x0040000,
        ProcessingStartRequested				= 0x0080000,
        ProcessingInProgress					= 0x0100000,
        ProcessingStopRequested					= 0x0200000,
        ProcessingStopped						= 0x0400000
    };

	Controller(std::shared_ptr<BlockingQueue> blockingQueue,
               std::shared_ptr<model::Model> model,
               View& view);
	virtual ~Controller();
	virtual void operator()();

	virtual void asyncStop();

	// view events
	virtual void visit(const common::StartRequestedMessage& message);
	virtual void visit(const common::StopRequestedMessage& message);
    virtual void visit(const common::RestartRequestedMessage& message);
    virtual void visit(const common::ExitRequestedMessage& message);
	virtual void visit(const common::FitnessFunctionChangeRequestedMessage& message);
    virtual void visit(const common::PerformSingleStepMessage& message);
    virtual void visit(const common::EvaluateGenerationMessage& message);
    virtual void visit(const common::InitializationOptionsChangeRequest& message);
    virtual void visit(const common::ReproductionOptionsChangeRequestedMessage& message);
    virtual void visit(const common::RangeOptionsChangeRequestedMessage& message);
    virtual void visit(const common::SelectionOptionsChangeRequestedMessage& message);
    virtual void visit(const common::GoalChangeRequestedMessage& message);
    virtual void visit(const common::MutationChangeRequestedMessage& message);
    virtual void visit(const common::PopulationSizeChangeRequestedMessage& message);
    virtual void visit(const common::CrossOverChangeRequestedMessage& message);

	// model events
	virtual void visit(const common::StateChangedMessage& message);
    virtual void visit(const common::GoalReachedMessage& message);
    virtual void visit(const common::ProcessingStartedMessage& message);
    virtual void visit(const common::ProcessingStoppedMessage& message);
    virtual void visit(const common::FitnessFunctionAppliedMessage& message);
    virtual void visit(const common::InitializationOptionsAppliedMessage& message);
    virtual void visit(const common::ReproductionOptionsAppliedMessage& message);
    virtual void visit(const common::MutationOptionsAppliedMessage& message);
    virtual void visit(const common::CrossOverOptionsAppliedMessage& message);
    virtual void visit(const common::RangeOptionsAppliedMessage& message);
    virtual void visit(const common::SelectionTypeChangeAppliedMessage& message);
    virtual void visit(const common::PopulationSizeChangeAppliedMessage& message);
    virtual void visit(const common::GoalValueChangeAppliedMessage& message);

	virtual void onStateChanged();
	virtual void onGoalReached();

	virtual void onProcessingStarted();
	virtual void onProcessingStoped();

    virtual void onFitnessFunctionApplied(const std::string& fitnessFunction);
	virtual void onInitializationOptionsApplied();
	virtual void onReproductionOptionsApplied();
	virtual void onMutationOptionsApplied();
	virtual void onCrossOverOptionsApplied();
    virtual void onRangeOptionsApplied();
	virtual void onSelectionTypeApplied();
	virtual void onPopulationSizeApplied();
	virtual void onGoalValueApplied();

private:
	void dispatchMessage(std::unique_ptr<common::Message> message);
    void setupModel();
    void updateControlls();

    std::shared_ptr<BlockingQueue> blockingQueue;
	std::shared_ptr<model::Model> model;
    View& view;
	std::atomic<bool> working;
    int state;

    std::string fitnessFunctionLastApplied;

    std::shared_ptr<common::RangeAlignmentOptions> requestedRangeOptions;
    std::shared_ptr<common::RangeAlignmentOptions> rangeOptionsSet;
};

