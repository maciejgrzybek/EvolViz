#pragma once
#include <memory>
#include "ModelOptions.h"
#include "Population.h"

namespace model {

struct Population;

class Selector {
public:
	class Factory : public common::SelectionOptionsVisitor {
	public:
		std::shared_ptr<Selector> produce(const common::SelectionOptions& options);

	public:
		virtual void visit(const common::EliteSelection& options) override;
		virtual void visit(const common::LoterySelection& options) override;
		virtual void visit(const common::TournamentSelection& options) override;
		virtual void visit(const common::RouletteSelection& options) override;

		std::shared_ptr<Selector> last_produced_;
	};

	virtual void operator()(Population& population, unsigned int size) const = 0;
};

class EliteSelector : public Selector {
public:
	virtual void operator()(Population& population, unsigned int size) const override;
};

class LoterySelector : public Selector {
public:
	virtual void operator()(Population& population, unsigned int size) const override;
};

class TournamentSelector : public Selector {
public:
	virtual void operator()(Population& population, unsigned int size) const override;
};

class RouletteSelector : public Selector {
public:
    RouletteSelector(double normalizator);
	virtual void operator()(Population& population, unsigned int size) const override;

private:
    double normalizator_;
};

typedef std::shared_ptr<Selector> SelectorPtr;

} // namespace model
