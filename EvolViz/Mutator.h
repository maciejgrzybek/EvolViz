#pragma once
#include <memory>
#include "ModelOptions.h"

namespace model {

struct Population;

class Mutator {
public:
	class Factory : public common::MutationOptionsVisitor {
	public:
		std::shared_ptr<Mutator> produce(const common::MutationOptions& options);

	public:
		virtual void visit(const common::UniversalRandomMutation& options) override;
		virtual void visit(const common::GaussRandomMutation& options) override;
		virtual void visit(const common::ConstMutation& options) override;

		std::shared_ptr<Mutator> last_produced_;
	};

	Mutator(const double mutation_rate);
	virtual void operator()(Population& population) const = 0;

protected:
	const double mutation_rate_;
};

class UniRandMutator : public Mutator {
public:
	UniRandMutator(const double mutation_rate, const common::UniversalRandomOptions x, const common::UniversalRandomOptions y);
	virtual void operator()(Population& population) const override;

private:
	const common::UniversalRandomOptions x_uni_;
	const common::UniversalRandomOptions y_uni_;
};

class GaussRandMutator : public Mutator {
public:
	GaussRandMutator(const double mutation_rate, const common::GaussRandomOptions x, const common::GaussRandomOptions y);
	virtual void operator()(Population& population) const override;

private:
	const common::GaussRandomOptions x_gauss_;
	const common::GaussRandomOptions y_gauss_;
};

class ConstMutator : public Mutator {
public:
	ConstMutator(const double mutation_rate, const double x, const double y);
	virtual void operator()(Population& population) const override;

private:
	const double x_const_;
	const double y_const_;
};

typedef std::shared_ptr<Mutator> MutatorPtr;

} // namespace model
