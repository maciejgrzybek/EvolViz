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

FitnessFunctionChangeRequestedMessage::FitnessFunctionChangeRequestedMessage(const std::string& str)
    : formula(str)
{}

void FitnessFunctionChangeRequestedMessage::accept(MessageVisitor& visitor) const
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

} // namespace common
