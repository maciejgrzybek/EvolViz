#include "Message.h"

namespace common
{

bool MessagePriorityComparator::operator()(const MessagePtr& a, const MessagePtr& b) const
{
	if (isModelMessage(*a) && !isModelMessage(*b))
		return false;
	if (!isModelMessage(*a) && isModelMessage(*b))
		return true;
	
	return (a->creationTime > b->creationTime);
}

bool MessagePriorityComparator::isModelMessage(const Message& msg) const
{
	return (dynamic_cast<const ModelMessage*>(&msg) != nullptr);
}

Message::Message()
	: creationTime(std::chrono::system_clock::now())
{}

// view messages

void StartRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void StopRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void RestartRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

void ExitRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

FitnessFunctionChangeRequestedMessage::FitnessFunctionChangeRequestedMessage(const std::string& str)
    : formula(str)
{}

void FitnessFunctionChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

ReproductionOptionsChangeRequestedMessage::ReproductionOptionsChangeRequestedMessage(double value)
    : value(value)
{}

void ReproductionOptionsChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

RangeOptionsChangeRequestedMessage::RangeOptionsChangeRequestedMessage(std::shared_ptr<RangeAlignmentOptions> options)
    : options(options)
{}

void RangeOptionsChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

SelectionOptionsChangeRequestedMessage::SelectionOptionsChangeRequestedMessage(std::shared_ptr<SelectionOptions> options)
    : options(options)
{}

void SelectionOptionsChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

GoalChangeRequestedMessage::GoalChangeRequestedMessage(double goal)
    : goal(goal)
{}

void GoalChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

MutationChangeRequestedMessage::MutationChangeRequestedMessage(std::shared_ptr<MutationOptions> options)
    : options(options)
{}

void MutationChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

PopulationSizeChangeRequestedMessage::PopulationSizeChangeRequestedMessage(int size)
    : size(size)
{}

void PopulationSizeChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

CrossOverChangeRequestedMessage::CrossOverChangeRequestedMessage(std::shared_ptr<CrossOverOptions> options)
    : options(options)
{}

void CrossOverChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

void PerformSingleStepMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

void EvaluateGenerationMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

InitializationOptionsChangeRequest::InitializationOptionsChangeRequest(Type type)
    : type(type)
{}

void InitializationOptionsChangeRequest::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

// model observed events

void StateChangedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void GoalReachedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void ProcessingStartedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void ProcessingStoppedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

FitnessFunctionAppliedMessage::FitnessFunctionAppliedMessage(const std::string& fitnessFunction)
    : fitnessFunction(fitnessFunction)
{}

void FitnessFunctionAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void InitializationOptionsAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void ReproductionOptionsAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void MutationOptionsAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void CrossOverOptionsAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

//RangeOptionsAppliedMessage::RangeOptionsAppliedMessage(std::shared_ptr<RangeAlignmentOptions> options)
//    : options(options)
//{}

void RangeOptionsAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void SelectionTypeChangeAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void PopulationSizeChangeAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void GoalValueChangeAppliedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void RestartPerformedMessage::accept(MessageVisitor& visitor) const
{
    visitor.visit(*this);
}

} // namespace common
