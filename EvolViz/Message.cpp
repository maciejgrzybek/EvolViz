#include "Message.h"

namespace common
{

void StartRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

void StopRequestedMessage::accept(MessageVisitor& visitor) const
{
	visitor.visit(*this);
}

} // namespace common