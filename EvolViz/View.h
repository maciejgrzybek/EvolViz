#pragma once

#include "GraphDescription.h"

class View
{
public:
	virtual ~View();

	virtual void drawGraph(const common::GraphDescription& graph) = 0;
};

