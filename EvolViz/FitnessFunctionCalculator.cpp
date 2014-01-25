#include "FitnessFunctionCalculator.h"

namespace common {

FitnessFunctionCalculator::InvalidFormulaException::InvalidFormulaException(const std::string& formula)
	: formula_(formula),
	  error_mgs_("Provided formula: \"" + formula + "\", is invalid.") {
}
const char* FitnessFunctionCalculator::InvalidFormulaException::what() const throw() {
	return "Provided formula is invalid.";
}
const std::string& FitnessFunctionCalculator::InvalidFormulaException::formula() {
	return formula_;
}

FitnessFunctionCalculator::FitnessFunctionCalculator(const std::string& formula) {
	exprtk::symbol_table<double> symbol_table;
	symbol_table.add_variable("x", x_);
	symbol_table.add_variable("y", y_);
	symbol_table.add_constants();

	expression_.register_symbol_table(symbol_table);

	exprtk::parser<double> parser;
	if (!parser.compile(formula, expression_))
		throw InvalidFormulaException(formula);
}

double FitnessFunctionCalculator::operator()(double x, double y) {
	x_ = x;
	y_ = y;
	return expression_.value();
}

} // namespace common
