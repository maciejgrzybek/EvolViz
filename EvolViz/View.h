#pragma once

#include "Model.h"

class View
{
public:
	virtual ~View();

    virtual void exit() = 0;

    virtual void drawGraph(const common::PopulationSnapshot& snapshot) = 0;
    virtual void changeFitnessFunction(const std::string& formula, double width, double height) = 0;

	virtual void onFunctionParsingCompleted() = 0;
	virtual void onFunctionParsingFailed() = 0;

    virtual void onExecutionAvailable() = 0;
    virtual void onExecutionNoMoreAvailable() = 0;
};

