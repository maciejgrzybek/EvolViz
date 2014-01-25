#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Crosser {
public:
	class Factory : public common::CrossOverOptionsVisitor {
	public:
		std::shared_ptr<Crosser> produce(const common::CrossOverOptions& options);

	public:
		virtual void visit(const common::ConstAvgCrossOver& options) override;
		virtual void visit(const common::UniversalRandomAvgCrossOver& options) override;
		virtual void visit(const common::GaussRandomAvgCrossOver& options) override;
		virtual void visit(const common::UniversalRandomFixedCrossOver& options) override;

		std::shared_ptr<Crosser> last_produced_;
	};

	Crosser(double cross_over_factor);
	virtual void operator()(Population& population) const = 0;

protected:
	double cross_over_factor_;
};

class ConstAvgCrosser : public Crosser {
public:
	ConstAvgCrosser(double cross_over_factor, double x_weight, double y_weight);
	virtual void operator()(Population& population) const override;

private:
	double x_weight_;
	double y_weight_;
};

class UniAvgCrosser : public Crosser {
public:
	UniAvgCrosser(double cross_over_factor, common::UniversalRandomOptions x, common::UniversalRandomOptions y);
	virtual void operator()(Population& population) const override;

private:
	common::UniversalRandomOptions x_uni_;
	common::UniversalRandomOptions y_uni_;
};

class GaussAvgCrosser : public Crosser {
public:
	GaussAvgCrosser(double cross_over_factor, common::GaussRandomOptions x, common::GaussRandomOptions y);
	virtual void operator()(Population& population) const override;

private:
	common::GaussRandomOptions x_gauss_;
	common::GaussRandomOptions y_gauss_;
};

class UniFixedCrosser : public Crosser {
public:
	UniFixedCrosser(double cross_over_factor);
	virtual void operator()(Population& population) const override;
};

typedef std::shared_ptr<Crosser> CrosserPtr;

} // namespace model
