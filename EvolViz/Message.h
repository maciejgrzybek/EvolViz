#pragma

#include <memory>

#include "Visitor.h"

namespace common
{

class Message;
class StartRequestedMessage;
class StopRequestedMessage;

typedef Visitor<StartRequestedMessage, StopRequestedMessage> MessageVisitor;

typedef std::unique_ptr<Message> MessagePtr;

struct Message
{
	virtual void accept(MessageVisitor& visitor) const = 0;
};

struct StartRequestedMessage : Message
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct StopRequestedMessage : Message
{
	virtual void accept(MessageVisitor& visitor) const;
};

} // namespace common