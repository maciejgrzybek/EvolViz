#pragma once

#include <chrono>
#include <memory>

#include "Visitor.h"

namespace common
{

struct StartRequestedMessage;
struct StopRequestedMessage;
struct FitnessFunctionChangeRequestedMessage;

struct StateChangedMessage;

typedef Visitor<StartRequestedMessage, StopRequestedMessage, FitnessFunctionChangeRequestedMessage, StateChangedMessage> MessageVisitor;

struct Message;

typedef std::unique_ptr<Message> MessagePtr;

struct MessagePriorityComparator
{
	bool operator()(const MessagePtr& a, const MessagePtr& b) const;

private:
	inline bool isModelMessage(const Message& msg) const;
};

struct Message
{
	Message();
	virtual void accept(MessageVisitor& visitor) const = 0;

	const std::chrono::time_point<std::chrono::system_clock> creationTime;
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

struct FitnessFunctionChangeRequestedMessage : ViewMessage
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
