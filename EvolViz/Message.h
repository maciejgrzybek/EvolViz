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
struct GoalReachedMessage;
struct ProcessingStartedMessage;
struct ProcessingStoppedMessage;
struct FitnessFunctionAppliedMessage;
struct InitializationOptionsAppliedMessage;
struct ReproductionOptionsAppliedMessage;
struct MutationOptionsAppliedMessage;
struct CrossOverOptionsAppliedMessage;
struct RangeOptionsAppliedMessage;
struct SelectionTypeChangeAppliedMessage;
struct PopulationSizeChangeAppliedMessage;
struct GoalValueChangeAppliedMessage;

typedef Visitor<StartRequestedMessage, StopRequestedMessage, FitnessFunctionChangeRequestedMessage, // view messages
				StateChangedMessage, // model messages below
				GoalReachedMessage,
				ProcessingStartedMessage,
				ProcessingStoppedMessage,
				FitnessFunctionAppliedMessage,
				InitializationOptionsAppliedMessage,
				ReproductionOptionsAppliedMessage,
				MutationOptionsAppliedMessage,
				CrossOverOptionsAppliedMessage,
				RangeOptionsAppliedMessage,
				SelectionTypeChangeAppliedMessage,
				PopulationSizeChangeAppliedMessage,
				GoalValueChangeAppliedMessage> MessageVisitor;

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

struct GoalReachedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct ProcessingStartedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct ProcessingStoppedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct FitnessFunctionAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct InitializationOptionsAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct ReproductionOptionsAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct MutationOptionsAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct CrossOverOptionsAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct RangeOptionsAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct SelectionTypeChangeAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct PopulationSizeChangeAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

struct GoalValueChangeAppliedMessage : ModelMessage
{
	virtual void accept(MessageVisitor& visitor) const;
};

} // namespace common
