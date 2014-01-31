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
    setupModel();
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

void Controller::visit(const common::StartRequestedMessage& /*message*/)
{
	// FIXME implement this
}

void Controller::visit(const common::StopRequestedMessage& /*message*/)
{
	// FIXME implement this
}

void Controller::visit(const common::RestartRequestedMessage& /*message*/)
{
    model->doRestart();
}

void Controller::visit(const common::ExitRequestedMessage& /*message*/)
{
    model->doExit();
    view.exit();
    working = false;
}

bool Controller::isFormulaCorrect(const std::string& formula) const
{
    try
    {
        common::FitnessFunctionCalculator calculator(formula);
        calculator(0, 0); // trivial check, exemplary (x,y)
    }
    catch (const common::FitnessFunctionCalculator::InvalidFormulaException&)
    {
        return false;
    }
    return true;
}

void Controller::visit(const common::FitnessFunctionChangeRequestedMessage& message)
{
    // TODO check whether in proper state (whether CAN change fitness function)!
    if (message.formula == fitnessFunctionLastApplied && !fitnessFunctionLastApplied.empty())
        return; // if not changed, do not update

    if (!isFormulaCorrect(message.formula))
        return view.onFunctionParsingFailed();

    model->setFitnessFunction(message.formula);
    model->doCommit(); // to ensure drawing function

    state = getBitmaskWithoutBitOn(state, State::FitnessFunctionChangeApplied);
    state |= State::FitnessFunctionChangeRequested;

    view.onFunctionParsingCompleted();
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

    state = getBitmaskWithoutBitOn(state, InitializationOptionsChangeApplied);
    state |= InitializationOptionsChangeRequested;
}

void Controller::visit(const common::ReproductionOptionsChangeRequestedMessage& message)
{
    // TODO check state
    model->setReproductionOptions(common::ReproductionOptions(message.value));

    state = getBitmaskWithoutBitOn(state, ReproductionOptionsChangeApplied);
    state |= ReproductionOptionsChangeRequested;
}

void Controller::visit(const common::RangeOptionsChangeRequestedMessage& message)
{
    requestedRangeOptions = message.options;
    model->setRangeOptions(*message.options);
    model->doCommit();

    state = getBitmaskWithoutBitOn(state, RangeOptionsChangeApplied);
    state |= RangeOptionsChangeRequested;
}

void Controller::visit(const common::SelectionOptionsChangeRequestedMessage& message)
{
    model->setSelectionType(*message.options);
    model->doCommit();

    state = getBitmaskWithoutBitOn(state, SelectionTypeChangeApplied);
    state |= SelectionTypeChangeRequested;
}

void Controller::visit(const common::GoalChangeRequestedMessage& message)
{
    model->setGoalValue(message.goal);
    model->doCommit();

    state = getBitmaskWithoutBitOn(state, GoalValueChangeApplied);
    state |= GoalValueChangeRequested;
}

void Controller::visit(const common::MutationChangeRequestedMessage& message)
{
    model->setMutationOptions(*message.options);
    model->doCommit();

    state = getBitmaskWithoutBitOn(state, MutationOptionsChangeApplied);
    state |= MutationOptionsChangeRequested;
}

void Controller::visit(const common::PopulationSizeChangeRequestedMessage& message)
{
    model->setPopulationSize(message.size);
    model->doCommit();

    state = getBitmaskWithoutBitOn(state, PopulationSizeChangeApplied);
    state |= PopulationSizeChangeRequested;
}

void Controller::visit(const common::CrossOverChangeRequestedMessage& message)
{
    model->setCrossOverOptions(*message.options);

    state = getBitmaskWithoutBitOn(state, CrossOverOptionsChangeApplied);
    state |= CrossOverOptionsChangeRequested;
}

void Controller::visit(const common::StateChangedMessage& /*message*/)
{
    lastSnapshot = model->getPopulationSnapshot();
    view.drawGraph(lastSnapshot);
}

void Controller::visit(const common::GoalReachedMessage&)
{
    // assuming snapshot is sorted!
    view.onGoalReached(model->getGenerationId(), lastSnapshot.subjects[0]);

    state |= GoalReached;
}

void Controller::visit(const common::ProcessingStartedMessage& /*message*/)
{
    // FIXME implement this
}

void Controller::visit(const common::ProcessingStoppedMessage& /*message*/)
{
    // FIXME implement this
}

void Controller::visit(const common::FitnessFunctionAppliedMessage& message)
{
    if (rangeOptionsSet)
    {
        const double width = rangeOptionsSet->x_max - rangeOptionsSet->x_min;
        const double height = rangeOptionsSet->y_max - rangeOptionsSet->y_min;
        view.changeFitnessFunction(message.fitnessFunction, width, height);
    }

    fitnessFunctionLastApplied = message.fitnessFunction;

    state = getBitmaskWithoutBitOn(state, FitnessFunctionChangeRequested);
    state |= FitnessFunctionChangeApplied;
}

void Controller::visit(const common::InitializationOptionsAppliedMessage&)
{
    state = getBitmaskWithoutBitOn(state, InitializationOptionsChangeRequested);
    state |= InitializationOptionsChangeApplied;
}

void Controller::visit(const common::ReproductionOptionsAppliedMessage&)
{
    state = getBitmaskWithoutBitOn(state, ReproductionOptionsChangeRequested);
    state |= ReproductionOptionsChangeApplied;
}

void Controller::visit(const common::MutationOptionsAppliedMessage&)
{
    state = getBitmaskWithoutBitOn(state, MutationOptionsChangeRequested);
    state |= MutationOptionsChangeApplied;
}

void Controller::visit(const common::CrossOverOptionsAppliedMessage&)
{
    state = getBitmaskWithoutBitOn(state, CrossOverOptionsChangeRequested);
    state |= CrossOverOptionsChangeApplied;
}

void Controller::visit(const common::RangeOptionsAppliedMessage& /*message*/)
{
    rangeOptionsSet = requestedRangeOptions;

    {
        const double width = rangeOptionsSet->x_max - rangeOptionsSet->x_min;
        const double height = rangeOptionsSet->y_max - rangeOptionsSet->y_min;
        view.changeFitnessFunction(fitnessFunctionLastApplied, width, height);
    }

    state = getBitmaskWithoutBitOn(state, RangeOptionsChangeRequested);
    state |= RangeOptionsChangeApplied;
}

void Controller::visit(const common::SelectionTypeChangeAppliedMessage&)
{
    state = getBitmaskWithoutBitOn(state, SelectionTypeChangeRequested);
    state |= SelectionTypeChangeApplied;
}

void Controller::visit(const common::PopulationSizeChangeAppliedMessage&)
{
    state = getBitmaskWithoutBitOn(state, PopulationSizeChangeRequested);
    state |= PopulationSizeChangeApplied;
}

void Controller::visit(const common::GoalValueChangeAppliedMessage&)
{
    state = getBitmaskWithoutBitOn(state, GoalValueChangeRequested);
    state |= GoalValueChangeApplied;
}

void Controller::visit(const common::RestartPerformedMessage&)
{
    state = getBitmaskWithoutBitOn(state, GoalReached);
    view.onRestartComplete();
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

void Controller::onRestarted()
{
    common::MessagePtr msg(new common::RestartPerformedMessage);
    blockingQueue->push(std::move(msg));
}

void Controller::onFitnessFunctionApplied(const std::string& fitnessFunction)
{
    common::MessagePtr msg(new common::FitnessFunctionAppliedMessage(fitnessFunction));
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

int Controller::getBitmaskWithoutBitOn(int bitmask, int bitToTurnOff)
{
    int result = bitmask;
    if (bitmask & bitToTurnOff)
        result ^= bitToTurnOff;

    return result;
}

void Controller::dispatchMessage(std::unique_ptr<common::Message> message)
{
	message->accept(*this);
    updateControlls();
}

void Controller::setupModel()
{
    using namespace common;
    visit(RangeOptionsChangeRequestedMessage(std::make_shared<MirroringRangeAlignment>(0, 5, 0, 5)));
    visit(FitnessFunctionChangeRequestedMessage("sin(x) + sin(y)"));
    {
        auto v = InitializationOptionsChangeRequest(InitializationOptionsChangeRequest::Random);
        v.x1 = 0;
        v.x2 = 5;
        v.y1 = 0;
        v.y2 = 5;
        visit(v);
    }
    visit(ReproductionOptionsChangeRequestedMessage(2.0));
    visit(MutationChangeRequestedMessage(std::shared_ptr<MutationOptions>(new GaussRandomMutation(0.25,
                                                                                                  common::GaussRandomOptions(0.0, 0.3),
                                                                                                  common::GaussRandomOptions(0.0, 0.3)))));
    visit(CrossOverChangeRequestedMessage(std::shared_ptr<CrossOverOptions>(new QualityAvgCrossOver(1.0, -2.0))));
    visit(SelectionOptionsChangeRequestedMessage(std::shared_ptr<SelectionOptions>(new LoterySelection)));
    visit(PopulationSizeChangeRequestedMessage(1000));
    visit(GoalChangeRequestedMessage(2.0));
}

void Controller::updateControlls()
{
    view.setControllsAvailability(static_cast<common::ControllsState>(state));
    /*
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
