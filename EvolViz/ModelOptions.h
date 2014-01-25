#pragma once
namespace common {
	/* Randomness options */
	struct UniversalRandomOptions {
		double min;
		double max;
	};
	struct GaussRandomOptions {
		double expected;
		double variation;
	};

	/* Initialization options */
	struct InitializationOptions {};
	struct PointInitialization : public InitializationOptions {
		double x;
		double y;
	};
	struct RandomInitialization : public InitializationOptions {};

	/* Mutation options */
	struct MutationOptions {
		double mutation_rate;
	};
	struct UniversalRandomMutation : public MutationOptions {
		UniversalRandomOptions x;
		UniversalRandomOptions y;
	};
	struct GaussRandomMutation : public MutationOptions {
		GaussRandomOptions x;
		GaussRandomOptions y;
	};
	struct ConstMutation : public MutationOptions {
		double value;
	};

	struct ReproductionOptions {
		double rate;
	};

	/* Crossover options */
	struct CrossOverOptions {
		double cross_over_factor;
	};
	struct ConstAvgCrossOver : public CrossOverOptions {
		double x_weight;
		double y_weight;
	};
	struct UniversalRandomAvgCrossOver : public CrossOverOptions {
		UniversalRandomOptions x;
		UniversalRandomOptions y;
	};
	struct GaussRandomAvgCrossOver : public CrossOverOptions {
		GaussRandomOptions x;
		GaussRandomOptions y;
	};
	struct UniversalRandomFixedCrossOver : public CrossOverOptions {};

	/* Alignment options */
	struct RangeAlignmentOptions {
		double x_min;
		double x_max;
		double y_min;
		double y_max;
	};
	struct RollingRangeAlignment : public RangeAlignmentOptions {};
	struct MirroringRangeAlignment : public RangeAlignmentOptions {};
	struct UniversalRandomReinitializationAlignment : public RangeAlignmentOptions {};

	/* Selection options */
	struct SelectionType {
		enum type { ELITE, LOTERY, TOURNAMENT, ROULETTE };
	};
} // namespace common
