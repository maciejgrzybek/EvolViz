#pragma once
#include "Visitor.h"

namespace common {
	struct PointInitialization;
	struct RandomInitialization;
	struct UniversalRandomMutation;
	struct GaussRandomMutation;
	struct ConstMutation;
	struct QualityAvgCrossOver;
	struct ConstAvgCrossOver;
	struct UniversalRandomAvgCrossOver;
	struct GaussRandomAvgCrossOver;
	struct UniversalRandomFixedCrossOver;
	struct QualityRandomFixedCrossOver;
	struct RollingRangeAlignment;
	struct MirroringRangeAlignment;
	struct UniversalRandomReinitializationAlignment;
	struct EliteSelection;
	struct LoterySelection;
	struct TournamentSelection;
	struct RouletteSelection;

	/* Randomness options */
	struct UniversalRandomOptions {
		double min;
		double max;
		UniversalRandomOptions();
		UniversalRandomOptions(double min, double max);
	};
	struct GaussRandomOptions {
		double expected;
		double variation;
		GaussRandomOptions();
		GaussRandomOptions(double expected, double variation);
	};

	/* Initialization options */
	typedef Visitor<PointInitialization, RandomInitialization> InitializationOptionsVisitor;
	struct InitializationOptions {
		virtual void accept(InitializationOptionsVisitor& visitor) const = 0;
	};
	struct PointInitialization : public InitializationOptions {
		double x;
		double y;
		PointInitialization(double x, double y);
		virtual void accept(InitializationOptionsVisitor& visitor) const override;
	};
	struct RandomInitialization : public InitializationOptions {
		double x_min;
		double x_max;
		double y_min;
		double y_max;
		RandomInitialization(double x_min, double x_max, double y_min, double y_max);
		virtual void accept(InitializationOptionsVisitor& visitor) const override;
	};

	/* Mutation options */
	typedef Visitor<UniversalRandomMutation, GaussRandomMutation, ConstMutation> MutationOptionsVisitor;
	struct MutationOptions {
		double mutation_rate;
		virtual void accept(MutationOptionsVisitor& visitor) const = 0;
		MutationOptions(double mutation_rate);
	};
	struct UniversalRandomMutation : public MutationOptions {
		UniversalRandomOptions x;
		UniversalRandomOptions y;
		UniversalRandomMutation(double mutation_rate, UniversalRandomOptions x, UniversalRandomOptions y);
		virtual void accept(MutationOptionsVisitor& visitor) const override;
	};
	struct GaussRandomMutation : public MutationOptions {
		GaussRandomOptions x;
		GaussRandomOptions y;
		GaussRandomMutation(double mutation_rate, GaussRandomOptions x, GaussRandomOptions y);
		virtual void accept(MutationOptionsVisitor& visitor) const override;
	};
	struct ConstMutation : public MutationOptions {
		double x;
		double y;
		ConstMutation(double mutation_rate, double x, double y);
		virtual void accept(MutationOptionsVisitor& visitor) const override;
	};

	struct ReproductionOptions {
		double rate;
		ReproductionOptions(double rate);
	};

	/* Crossover options */
	typedef Visitor<QualityAvgCrossOver, ConstAvgCrossOver, UniversalRandomAvgCrossOver, GaussRandomAvgCrossOver, QualityRandomFixedCrossOver, UniversalRandomFixedCrossOver> CrossOverOptionsVisitor;
	struct CrossOverOptions {
		double cross_over_factor;
		CrossOverOptions(double cross_over_factor);
		virtual void accept(CrossOverOptionsVisitor& visitor) const = 0;
	};
	struct QualityAvgCrossOver : public CrossOverOptions {
		double normalizator;
		QualityAvgCrossOver(double cross_over_factor, double normalizator);
		virtual void accept(CrossOverOptionsVisitor& visitor) const override;
	};
	struct ConstAvgCrossOver : public CrossOverOptions {
		double x_weight[2];
		double y_weight[2];
        ConstAvgCrossOver(double cross_over_factor, const double x_weight[2], const double y_weight[2]);
		virtual void accept(CrossOverOptionsVisitor& visitor) const override;
	};
	struct UniversalRandomAvgCrossOver : public CrossOverOptions {
		UniversalRandomOptions x[2];
		UniversalRandomOptions y[2];
        UniversalRandomAvgCrossOver(double cross_over_factor, const UniversalRandomOptions x[2], const UniversalRandomOptions y[2]);
		virtual void accept(CrossOverOptionsVisitor& visitor) const override;
	};
	struct GaussRandomAvgCrossOver : public CrossOverOptions {
		GaussRandomOptions x[2];
		GaussRandomOptions y[2];
        GaussRandomAvgCrossOver(double cross_over_factor, const GaussRandomOptions x[2], const GaussRandomOptions y[2]);
		virtual void accept(CrossOverOptionsVisitor& visitor) const override;
	};
	struct QualityRandomFixedCrossOver : public CrossOverOptions {
		double normalizator;
		QualityRandomFixedCrossOver(double cross_over_factor, double normalizator);
		virtual void accept(CrossOverOptionsVisitor& visitor) const override;
	};
	struct UniversalRandomFixedCrossOver : public CrossOverOptions {
		UniversalRandomFixedCrossOver(double cross_over_factor);
		virtual void accept(CrossOverOptionsVisitor& visitor) const override;
	};

	/* Alignment options */
	typedef common::Visitor<RollingRangeAlignment, MirroringRangeAlignment, UniversalRandomReinitializationAlignment> RangeAlignmentOptionsVisitor;
	struct RangeAlignmentOptions {
		double x_min;
		double x_max;
		double y_min;
		double y_max;
		RangeAlignmentOptions(double x_min, double x_max, double y_min, double y_max);
		virtual void accept(RangeAlignmentOptionsVisitor& visitor) const = 0;
	};
	struct RollingRangeAlignment : public RangeAlignmentOptions {
		RollingRangeAlignment(double x_min, double x_max, double y_min, double y_max);
		virtual void accept(RangeAlignmentOptionsVisitor& visitor) const override;
	};
	struct MirroringRangeAlignment : public RangeAlignmentOptions {
		MirroringRangeAlignment(double x_min, double x_max, double y_min, double y_max);
		virtual void accept(RangeAlignmentOptionsVisitor& visitor) const override;
	};
	struct UniversalRandomReinitializationAlignment : public RangeAlignmentOptions {
		UniversalRandomReinitializationAlignment(double x_min, double x_max, double y_min, double y_max);
		virtual void accept(RangeAlignmentOptionsVisitor& visitor) const override;
	};

	/* Selection options */
	typedef common::Visitor<EliteSelection, LoterySelection, TournamentSelection, RouletteSelection> SelectionOptionsVisitor;
	struct SelectionOptions {
		virtual void accept(SelectionOptionsVisitor& visitor) const = 0;
	};
	struct EliteSelection : public SelectionOptions {
		virtual void accept(SelectionOptionsVisitor& visitor) const override;
	};
	struct LoterySelection : public SelectionOptions {
		virtual void accept(SelectionOptionsVisitor& visitor) const override;
	};
	struct TournamentSelection : public SelectionOptions {
		virtual void accept(SelectionOptionsVisitor& visitor) const override;
	};
	struct RouletteSelection : public SelectionOptions {
        double normalizator;
        RouletteSelection(double normalizator);
		virtual void accept(SelectionOptionsVisitor& visitor) const override;              
	};
} // namespace common
