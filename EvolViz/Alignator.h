#pragma once
#include <memory>
#include "ModelOptions.h"
#include "Population.h"

namespace model {

struct Population;

class Alignator {
public:	
	class Factory : public common::RangeAlignmentOptionsVisitor {
	public:
		std::shared_ptr<Alignator> produce(const common::RangeAlignmentOptions& options);

	public:
		virtual void visit(const common::RollingRangeAlignment& options) override;
		virtual void visit(const common::MirroringRangeAlignment& options) override;
		virtual void visit(const common::UniversalRandomReinitializationAlignment& options) override;

		std::shared_ptr<Alignator> last_produced_;
	};

	Alignator(double x_min, double x_max, double y_min, double y_max);
	virtual void operator()(Population& population) const = 0;

protected:
	bool isBelowXRange(const Population::Subject& subject) const;
	bool isOverXRange(const Population::Subject& subject) const;
	bool isBelowYRange(const Population::Subject& subject) const;
	bool isOverYRange(const Population::Subject& subject) const;
	bool isInRangeX(const Population::Subject& subject) const;
	bool isInRangeY(const Population::Subject& subject) const;
	double range_width_x() const;
	double range_width_y() const;
	double overflow_x(const Population::Subject& subject) const;
	double overflow_y(const Population::Subject& subject) const;

	const double x_min_;
	const double x_max_;
	const double y_min_;
	const double y_max_;
};

class RollingAlignator : public Alignator {
public:
	RollingAlignator(double x_min, double x_max, double y_min, double y_max);
	virtual void operator()(Population& population) const override;

private:
	void alignSubject(Population::Subject& subject) const;
};

class MirroringAlignator : public Alignator {
public:
	MirroringAlignator(double x_min, double x_max, double y_min, double y_max);
	virtual void operator()(Population& population) const override;

private:
	void alignSubject(Population::Subject& subject) const;
};

class ReinitializationAlignator : public Alignator {
public:
	ReinitializationAlignator(double x_min, double x_max, double y_min, double y_max);
	virtual void operator()(Population& population) const override;

private:
	void alignSubject(Population::Subject& subject) const;
};

typedef std::shared_ptr<Alignator> AlignatorPtr;

} // namespace model
