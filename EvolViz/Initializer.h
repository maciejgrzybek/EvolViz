#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Initializer {
public:
	class Factory : public common::InitializationOptionsVisitor {
	public:
		std::shared_ptr<Initializer> produce(const common::InitializationOptions& options);

	public:
		virtual void visit(const common::PointInitialization& options) override;
		virtual void visit(const common::RandomInitialization& options) override;

		std::shared_ptr<Initializer> last_produced_;
	};

	virtual void operator()(Population& population, unsigned int size) const = 0;
};

class PointInitializer : public Initializer {
public:
	PointInitializer(const double x, const double y);
	virtual void operator()(Population& population, unsigned int size) const override;

private:
	double x_;
	double y_;
};

class RandomInitializer : public Initializer {
public:
	virtual void operator()(Population& population, unsigned int size) const override;
};

typedef std::shared_ptr<Initializer> InitializerPtr;

} // namespace model
