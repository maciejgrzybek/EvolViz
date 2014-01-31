#pragma once

#include <chrono>
#include <memory>

#include "Visitor.h"
#include "ModelOptions.h"

namespace common
{

struct StartRequestedMessage;
struct StopRequestedMessage;
struct RestartRequestedMessage;
struct ExitRequestedMessage;
struct FitnessFunctionChangeRequestedMessage;
struct PerformSingleStepMessage;
struct EvaluateGenerationMessage;
struct InitializationOptionsChangeRequest;
struct ReproductionOptionsChangeRequestedMessage;
struct RangeOptionsChangeRequestedMessage;
struct SelectionOptionsChangeRequestedMessage;
struct GoalChangeRequestedMessage;
struct MutationChangeRequestedMessage;
struct PopulationSizeChangeRequestedMessage;
struct CrossOverChangeRequestedMessage;

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
struct RestartPerformedMessage;

typedef Visitor<StartRequestedMessage, // view messages
                StopRequestedMessage,
                RestartRequestedMessage,
                ExitRequestedMessage,
                FitnessFunctionChangeRequestedMessage,
                PerformSingleStepMessage,
                EvaluateGenerationMessage,
                InitializationOptionsChangeRequest,
                ReproductionOptionsChangeRequestedMessage,
                RangeOptionsChangeRequestedMessage,
                SelectionOptionsChangeRequestedMessage,
                GoalChangeRequestedMessage,
                MutationChangeRequestedMessage,
                PopulationSizeChangeRequestedMessage,
                CrossOverChangeRequestedMessage,
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
                GoalValueChangeAppliedMessage,
                RestartPerformedMessage> MessageVisitor;

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

struct RestartRequestedMessage : ViewMessage
{
    virtual void accept(MessageVisitor& visitor) const;
};

struct ExitRequestedMessage : ViewMessage
{
    virtual void accept(MessageVisitor& visitor) const;
};

struct FitnessFunctionChangeRequestedMessage : ViewMessage
{
    FitnessFunctionChangeRequestedMessage(const std::string& str);
    const std::string formula;
	virtual void accept(MessageVisitor& visitor) const;
};

struct ReproductionOptionsChangeRequestedMessage : ViewMessage
{
    ReproductionOptionsChangeRequestedMessage(double value);
    const double value;
    virtual void accept(MessageVisitor& visitor) const;
};

struct RangeOptionsChangeRequestedMessage : ViewMessage
{
    RangeOptionsChangeRequestedMessage(std::shared_ptr<RangeAlignmentOptions> options);
    std::shared_ptr<RangeAlignmentOptions> options;

    virtual void accept(MessageVisitor& visitor) const;
};

struct SelectionOptionsChangeRequestedMessage : ViewMessage
{
    SelectionOptionsChangeRequestedMessage(std::shared_ptr<SelectionOptions> options);
    std::shared_ptr<SelectionOptions> options;

    virtual void accept(MessageVisitor& visitor) const;
};

struct GoalChangeRequestedMessage : ViewMessage
{
    GoalChangeRequestedMessage(double goal);
    const double goal;

    virtual void accept(MessageVisitor& visitor) const;
};

struct MutationChangeRequestedMessage : ViewMessage
{
    MutationChangeRequestedMessage(std::shared_ptr<common::MutationOptions> options);
    std::shared_ptr<common::MutationOptions> options;

    virtual void accept(MessageVisitor& visitor) const;
};

struct PopulationSizeChangeRequestedMessage : ViewMessage
{
    PopulationSizeChangeRequestedMessage(int size);
    const int size;

    virtual void accept(MessageVisitor& visitor) const;
};

struct CrossOverChangeRequestedMessage : ViewMessage
{
    CrossOverChangeRequestedMessage(std::shared_ptr<common::CrossOverOptions> options);
    const std::shared_ptr<common::CrossOverOptions> options;

    virtual void accept(MessageVisitor& visitor) const;
};

struct PerformSingleStepMessage : ViewMessage
{
    virtual void accept(MessageVisitor& visitor) const;
};

struct EvaluateGenerationMessage : ViewMessage
{
    virtual void accept(MessageVisitor& visitor) const;
};

struct InitializationOptionsChangeRequest : ViewMessage
{
    enum Type { Point, Random };
    InitializationOptionsChangeRequest(Type type);

    const Type type;

    double x1; // min
    double y1; // min
    double x2; // max
    double y2; // max

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
    FitnessFunctionAppliedMessage(const std::string& fitnessFunction);
    const std::string fitnessFunction;

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
    //RangeOptionsAppliedMessage(std::shared_ptr<common::RangeAlignmentOptions> options);
    //const std::shared_ptr<common::RangeAlignmentOptions> options;

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

struct RestartPerformedMessage : ModelMessage
{
    virtual void accept(MessageVisitor& visitor) const;
};

} // namespace common
