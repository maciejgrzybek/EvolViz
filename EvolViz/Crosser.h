#pragma once
#include <memory>
#include "ModelOptions.h"
#include "Population.h"

namespace model {

struct Population;

class Crosser {
public:
	class Factory : public common::CrossOverOptionsVisitor {
	public:
		std::shared_ptr<Crosser> produce(const common::CrossOverOptions& options);

	public:
		virtual void visit(const common::QualityAvgCrossOver& options) override;
		virtual void visit(const common::ConstAvgCrossOver& options) override;
		virtual void visit(const common::UniversalRandomAvgCrossOver& options) override;
		virtual void visit(const common::GaussRandomAvgCrossOver& options) override;
		virtual void visit(const common::QualityRandomFixedCrossOver& options) override;
		virtual void visit(const common::UniversalRandomFixedCrossOver& options) override;

		std::shared_ptr<Crosser> last_produced_;
	};

	Crosser(const double cross_over_factor);
	virtual void operator()(Population& population) const = 0;

protected:
	const double cross_over_factor_;
};

class QualityAvgCrosser : public Crosser {
public:
	QualityAvgCrosser(const double cross_over_factor);
	virtual void operator()(Population& population) const override;

private:
	Population::Subject crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const;
};

class ConstAvgCrosser : public Crosser {
public:
	ConstAvgCrosser(const double cross_over_factor, const double x_weight[2], const double y_weight[2]);
	virtual void operator()(Population& population) const override;

private:
	Population::Subject crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const;
	const double x_weight_first_;
	const double y_weight_first_;
	const double x_weight_second_;
	const double y_weight_second_;
};

class UniAvgCrosser : public Crosser {
public:
	UniAvgCrosser(const double cross_over_factor, const common::UniversalRandomOptions x[2], const common::UniversalRandomOptions y[2]);
	virtual void operator()(Population& population) const override;

private:
	Population::Subject crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const;
	const common::UniversalRandomOptions x_uni_first_;
	const common::UniversalRandomOptions y_uni_first_;
	const common::UniversalRandomOptions x_uni_second_;
	const common::UniversalRandomOptions y_uni_second_;
};

class GaussAvgCrosser : public Crosser {
public:
	GaussAvgCrosser(const double cross_over_factor, const common::GaussRandomOptions x[2], const common::GaussRandomOptions y[2]);
	virtual void operator()(Population& population) const override;

private:
	Population::Subject crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const;
	const common::GaussRandomOptions x_gauss_first_;
	const common::GaussRandomOptions y_gauss_first_;
	const common::GaussRandomOptions x_gauss_second_;
	const common::GaussRandomOptions y_gauss_second_;
};

class QualityFixedCrosser : public Crosser {
public:
	QualityFixedCrosser(const double cross_over_factor);
	virtual void operator()(Population& population) const override;

private:
	Population::Subject crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const;
};

class UniFixedCrosser : public Crosser {
public:
	UniFixedCrosser(const double cross_over_factor);
	virtual void operator()(Population& population) const override;

private:
	Population::Subject crossSubjects(Population::Subject& subject_one, Population::Subject& subject_two) const;
};

typedef std::shared_ptr<Crosser> CrosserPtr;

} // namespace model
