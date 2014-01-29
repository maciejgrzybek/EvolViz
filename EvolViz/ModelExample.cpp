#include "ModelExample.h"

#include <iostream>
#include <thread>
#include <algorithm>

#include "Model.h"
#include "ModelObserver.h"
#include "ModelOptions.h"
#include "PopulationSnapshot.h"

namespace model {
namespace testing {

#define IOSTREAM_OBSERVER(event_name) \
	virtual void event_name() override { std::cout << "MyObserver::" #event_name << std::endl; }

class MyObserver : public common::ModelObserver {
public:
	MyObserver(Model& model)
		: model_(model) {
	}

	virtual void onStateChanged() override {
		common::PopulationSnapshot snapshot = model_.getPopulationSnapshot();
		std::sort(snapshot.subjects.begin(), snapshot.subjects.end());
		common::PopulationSnapshot::Subject best = snapshot.subjects[0];
		std::cout << "Best: (" << best.x << ", " << best.y << ") -> " << best.value << ";" << std::endl;
	}
	IOSTREAM_OBSERVER(onGoalReached);

	IOSTREAM_OBSERVER(onProcessingStarted);
	IOSTREAM_OBSERVER(onProcessingStoped);
	
	IOSTREAM_OBSERVER(onFitnessFunctionApplied);
	IOSTREAM_OBSERVER(onInitializationOptionsApplied);
	IOSTREAM_OBSERVER(onReproductionOptionsApplied);
	IOSTREAM_OBSERVER(onMutationOptionsApplied);
	IOSTREAM_OBSERVER(onCrossOverOptionsApplied);
	IOSTREAM_OBSERVER(onRangeOptionsApplied);
	IOSTREAM_OBSERVER(onSelectionTypeApplied);
	IOSTREAM_OBSERVER(onPopulationSizeApplied);
	IOSTREAM_OBSERVER(onGoalValueApplied);

private:
	Model& model_;
};

void engage() {
	std::cout << "Tworzenie modelu." << std::endl;
	Model model;
	MyObserver observer(model);
	model.addObserver(&observer);
	std::thread model_thread(std::ref(model));
	std::cout << "Watek modelu uruchomiony." << std::endl;

	// INITIALIZATION
	std::cout << "Inicjalizacja" << std::endl;
    model.setFitnessFunction("2");
	model.setInitializationOptions(common::RandomInitialization(0, 5, 0, 5));
	model.setReproductionOptions(common::ReproductionOptions(2.0));
	model.setMutationOptions(common::GaussRandomMutation(0.25, common::GaussRandomOptions(0.0, 0.3), common::GaussRandomOptions(0.0, 0.3)));
	model.setCrossOverOptions(common::QualityAvgCrossOver(1.0, -2.0));
	model.setRangeOptions(common::MirroringRangeAlignment(0, 5, 0, 5));
	model.setSelectionType(common::LoterySelection());
	model.setPopulationSize(1000);
	model.setGoalValue(1.9999);

	std::cout << "Wykonywanie" << std::endl;
	for (int i = 0; i < 200; ++i) {
		model.doGeneration();
	}

	model.doExit();
	model_thread.join();
	model.removeObserver(&observer);
}

} // namespace testing
} // namespace model
