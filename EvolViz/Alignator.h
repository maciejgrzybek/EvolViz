#pragma once
#include <memory>
#include "ModelOptions.h"

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
	double x_min_;
	double x_max_;
	double y_min_;
	double y_max_;
};

class RollingAlignator : public Alignator {
public:
	RollingAlignator(double x_min, double x_max, double y_min, double y_max);
	virtual void operator()(Population& population) const override;
};

class MirroringAlignator : public Alignator {
public:
	MirroringAlignator(double x_min, double x_max, double y_min, double y_max);
	virtual void operator()(Population& population) const override;
};

class ReinitializationAlignator : public Alignator {
public:
	ReinitializationAlignator(double x_min, double x_max, double y_min, double y_max);
	virtual void operator()(Population& population) const override;
};

typedef std::shared_ptr<Alignator> AlignatorPtr;

} // namespace model
