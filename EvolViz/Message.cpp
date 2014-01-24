#include "Message.h"

namespace common
{

// view messages

void StartRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void StopRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

// model observed events

void StateChangedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

} // namespace common