#pragma once
namespace common {

class ModelObserver
{
public:
	virtual ~ModelObserver();
	virtual void onStateChanged() = 0;
	virtual void onGoalReached() = 0;
	
	virtual void onProcessingStarted() = 0;
	virtual void onProcessingStoped() = 0;

	virtual void onFitnessFunctionApplied() = 0;
	virtual void onInitializationOptionsApplied() = 0;
	virtual void onReproductionOptionsApplied() = 0;
	virtual void onMutationOptionsApplied() = 0;
	virtual void onCrossOverOptionsApplied() = 0;
	virtual void onRangeOptionsApplied() = 0;
	virtual void onSelectionTypeApplied() = 0;
	virtual void onPopulationSizeApplied() = 0;
	virtual void onGoalValueApplied() = 0;
};

}

