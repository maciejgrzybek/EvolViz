#pragma once
#include "Visitor.h"

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
		void accept(common::Visitor<PointInitialization>& visitor);
	};
	struct RandomInitialization : public InitializationOptions {
		void accept(common::Visitor<RandomInitialization>& visitor);
	};

	/* Mutation options */
	struct MutationOptions {
		double mutation_rate;
	};
	struct UniversalRandomMutation : public MutationOptions {
		UniversalRandomOptions x;
		UniversalRandomOptions y;
		void accept(common::Visitor<UniversalRandomMutation>& visitor);
	};
	struct GaussRandomMutation : public MutationOptions {
		GaussRandomOptions x;
		GaussRandomOptions y;
		void accept(common::Visitor<GaussRandomMutation>& visitor);
	};
	struct ConstMutation : public MutationOptions {
		double value;
		void accept(common::Visitor<ConstMutation>& visitor);
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
		void accept(common::Visitor<ConstAvgCrossOver>& visitor);
	};
	struct UniversalRandomAvgCrossOver : public CrossOverOptions {
		UniversalRandomOptions x;
		UniversalRandomOptions y;
		void accept(common::Visitor<UniversalRandomAvgCrossOver>& visitor);
	};
	struct GaussRandomAvgCrossOver : public CrossOverOptions {
		GaussRandomOptions x;
		GaussRandomOptions y;
		void accept(common::Visitor<GaussRandomAvgCrossOver>& visitor);
	};
	struct UniversalRandomFixedCrossOver : public CrossOverOptions {
		void accept(common::Visitor<UniversalRandomFixedCrossOver>& visitor);
	};

	/* Alignment options */
	struct RangeAlignmentOptions {
		double x_min;
		double x_max;
		double y_min;
		double y_max;
	};
	struct RollingRangeAlignment : public RangeAlignmentOptions {
		void accept(common::Visitor<RollingRangeAlignment>& visitor);
	};
	struct MirroringRangeAlignment : public RangeAlignmentOptions {
		void accept(common::Visitor<MirroringRangeAlignment>& visitor);
	};
	struct UniversalRandomReinitializationAlignment : public RangeAlignmentOptions {
		void accept(common::Visitor<UniversalRandomReinitializationAlignment>& visitor);
	};

	/* Selection options */
	struct SelectionOptions {};
	struct EliteSelection : public SelectionOptions {
		void accept(common::Visitor<EliteSelection>& visitor);
	};
	struct LoterySelection : public SelectionOptions {
		void accept(common::Visitor<LoterySelection>& visitor);
	};
	struct TournamentSelection : public SelectionOptions {
		void accept(common::Visitor<TournamentSelection>& visitor);
	};
	struct RouletteSelection : public SelectionOptions {
		void accept(common::Visitor<RouletteSelection>& visitor);
	};
} // namespace common
