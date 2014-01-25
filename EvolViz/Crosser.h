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

	Crosser(const double cross_over_factor);
	virtual void operator()(Population& population) const = 0;

protected:
	const double cross_over_factor_;
};

class ConstAvgCrosser : public Crosser {
public:
	ConstAvgCrosser(const double cross_over_factor, const double x_weight, const double y_weight);
	virtual void operator()(Population& population) const override;

private:
	const double x_weight_;
	const double y_weight_;
};

class UniAvgCrosser : public Crosser {
public:
	UniAvgCrosser(const double cross_over_factor, const common::UniversalRandomOptions x, const common::UniversalRandomOptions y);
	virtual void operator()(Population& population) const override;

private:
	const common::UniversalRandomOptions x_uni_;
	const common::UniversalRandomOptions y_uni_;
};

class GaussAvgCrosser : public Crosser {
public:
	GaussAvgCrosser(const double cross_over_factor, const common::GaussRandomOptions x, const common::GaussRandomOptions y);
	virtual void operator()(Population& population) const override;

private:
	const common::GaussRandomOptions x_gauss_;
	const common::GaussRandomOptions y_gauss_;
};

class UniFixedCrosser : public Crosser {
public:
	UniFixedCrosser(const double cross_over_factor);
	virtual void operator()(Population& population) const override;
};

typedef std::shared_ptr<Crosser> CrosserPtr;

} // namespace model
