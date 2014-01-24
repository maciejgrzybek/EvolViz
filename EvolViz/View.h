#pragma once

#include "GraphDescription.h"

class View
{
public:
	virtual ~View();

	virtual void drawGraph(const common::GraphDescription& graph) = 0;
	virtual void changeFitnessFunction(/* some struct describing fitness function */) = 0;

	virtual void onFunctionParsingCompleted() = 0;
	virtual void onFunctionParsingFailed() = 0;
};

