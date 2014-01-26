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

void FitnessFunctionChangeRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

// model observed events

void StateChangedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

} // namespace common