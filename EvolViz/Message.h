#pragma

#include <memory>

#include "Visitor.h"

namespace common
{

struct StartRequestedMessage;
struct StopRequestedMessage;
struct StateChangedMessage;

typedef Visitor<StartRequestedMessage, StopRequestedMessage, StateChangedMessage> MessageVisitor;

struct Message;

typedef std::unique_ptr<Message> MessagePtr;

struct Message
{
	virtual void accept(MessageVisitor& visitor) const = 0;
};

struct ViewMessage : Message
{};

struct StartRequestedMessage : ViewMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct StopRequestedMessage : ViewMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct ModelMessage : Message
{};

struct StateChangedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

} // namespace common