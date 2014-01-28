#include "Controller.h"
#include "View.h"


Controller::Controller(std::shared_ptr<BlockingQueue> blockingQueue,
                       std::shared_ptr<model::Model> model,
                       View& view)
	: blockingQueue(blockingQueue),
      model(model),
      view(view),
      working(false),
      state(0)
{
    updateControlls();
}

Controller::~Controller()
{}

void Controller::operator()()
{
	working = true;
	while (working)
	{
		common::MessagePtr msg;
        bool wasAnythingPopped = blockingQueue->pop(msg);
        if (wasAnythingPopped)
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
    // TODO check whether in proper state (whether CAN change fitness function)!
    model->setFitnessFunction(message.formula);
    view.changeFitnessFunction(message.formula);
}

void Controller::visit(const common::PerformSingleStepMessage& message)
{/*
    if (state & State::FitnessFunctionChangeApplied
        && state & State::CrossOverOptionsChangeApplied
        && state & State::MutationOptionsChangeApplied
        && state & State::RangeOptionsChangeApplied
        && state & State::GoalValueChangeApplied
        && state & State::InitializationOptionsChangeApplied)*/
    {
        model->doStep();
    }
}

void Controller::visit(const common::EvaluateGenerationMessage& message)
{
//    if (state & State::FitnessFunctionChangeApplied
//        && state & State::CrossOverOptionsChangeApplied
//        && state & State::MutationOptionsChangeApplied
//        && state & State::RangeOptionsChangeApplied
//        && state & State::GoalValueChangeApplied
//        && state & State::InitializationOptionsChangeApplied)
    {
        model->doGeneration();
    }
}

void Controller::visit(const common::InitializationOptionsChangeRequest& message)
{
    // TODO check whether it is appropriate moment to change initialization options
    if (message.type == common::InitializationOptionsChangeRequest::Point)
        model->setInitializationOptions(common::PointInitialization(message.x1, message.y1));
    else
        model->setInitializationOptions(common::RandomInitialization(message.x1, message.x2, message.y1, message.y2));

    state ^= InitializationOptionsChangeApplied;
    state |= InitializationOptionsChangeRequested;
}

void Controller::visit(const common::ReproductionOptionsChangeRequestedMessage& message)
{
    // TODO check state
    model->setReproductionOptions(common::ReproductionOptions(message.value));

    state ^= ReproductionOptionsChangeApplied;
    state |= ReproductionOptionsChangeRequested;
}

void Controller::visit(const common::StateChangedMessage& message)
{
    common::PopulationSnapshot snapshot = model->getPopulationSnapshot();
    view.drawGraph(snapshot);
}

void Controller::visit(const common::GoalReachedMessage&)
{
    state |= GoalReached;
}

void Controller::visit(const common::ProcessingStartedMessage& message)
{
    // FIXME implement this
}

void Controller::visit(const common::ProcessingStoppedMessage& message)
{
    // FIXME implement this
}

void Controller::visit(const common::FitnessFunctionAppliedMessage&)
{
    state ^= FitnessFunctionChangeRequested;
    state |= FitnessFunctionChangeApplied;
}

void Controller::visit(const common::InitializationOptionsAppliedMessage&)
{
    state ^= InitializationOptionsChangeRequested;
    state |= InitializationOptionsChangeApplied;
}

void Controller::visit(const common::ReproductionOptionsAppliedMessage&)
{
    state ^= ReproductionOptionsChangeRequested;
    state |= ReproductionOptionsChangeApplied;
}

void Controller::visit(const common::MutationOptionsAppliedMessage&)
{
    state ^= MutationOptionsChangeRequested;
    state |= MutationOptionsChangeApplied;
}

void Controller::visit(const common::CrossOverOptionsAppliedMessage&)
{
    state ^= CrossOverOptionsChangeRequested;
    state |= CrossOverOptionsChangeApplied;
}

void Controller::visit(const common::RangeOptionsAppliedMessage&)
{
    state ^= RangeOptionsChangeRequested;
    state |= RangeOptionsChangeApplied;
}

void Controller::visit(const common::SelectionTypeChangeAppliedMessage&)
{
    state ^= SelectionTypeChangeRequested;
    state |= SelectionTypeChangeApplied;
}

void Controller::visit(const common::PopulationSizeChangeAppliedMessage&)
{
    state ^= PopulationSizeChangeRequested;
    state |= PopulationSizeChangeApplied;
}

void Controller::visit(const common::GoalValueChangeAppliedMessage&)
{
    state ^= GoalValueChangeRequested;
    state |= GoalValueChangeApplied;
}

void Controller::onStateChanged()
{
	// enqueue Message for further evaluation in proper (Controller's) thread.
	common::MessagePtr msg(new common::StateChangedMessage);
	blockingQueue->push(std::move(msg));
}

void Controller::onGoalReached()
{
    common::MessagePtr msg(new common::GoalReachedMessage);
    blockingQueue->push(std::move(msg));
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
    common::MessagePtr msg(new common::FitnessFunctionAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onInitializationOptionsApplied()
{
    common::MessagePtr msg(new common::InitializationOptionsAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onReproductionOptionsApplied()
{
    common::MessagePtr msg(new common::ReproductionOptionsAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onMutationOptionsApplied()
{
    common::MessagePtr msg(new common::MutationOptionsAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onCrossOverOptionsApplied()
{
    common::MessagePtr msg(new common::CrossOverOptionsAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onRangeOptionsApplied()
{
    common::MessagePtr msg(new common::RangeOptionsAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onSelectionTypeApplied()
{
    common::MessagePtr msg(new common::SelectionTypeChangeAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onPopulationSizeApplied()
{
    common::MessagePtr msg(new common::PopulationSizeChangeAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onGoalValueApplied()
{
    common::MessagePtr msg(new common::GoalValueChangeAppliedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::dispatchMessage(std::unique_ptr<common::Message> message)
{
	message->accept(*this);
}

void Controller::updateControlls()
{
    view.onExecutionAvailable();/*
    if (state & State::FitnessFunctionChangeApplied
        && state & State::CrossOverOptionsChangeApplied
        && state & State::MutationOptionsChangeApplied
        && state & State::RangeOptionsChangeApplied
        && state & State::GoalValueChangeApplied
        && state & State::InitializationOptionsChangeApplied
        && !(state & State::GoalReached))
        view.onExecutionAvailable();
    else
        view.onExecutionNoMoreAvailable();*/
}
