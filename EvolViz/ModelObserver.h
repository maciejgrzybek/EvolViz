#pragma once
class ModelObserver
{
public:
	virtual ~ModelObserver();
	virtual void onStateChanged() = 0;
	// TODO add more events
};

