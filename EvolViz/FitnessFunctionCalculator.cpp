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
    try {
      calculator_.DefineVar("x", &x_);
      calculator_.DefineVar("y", &y_);
      calculator_.SetExpr(formula);
    } catch (mu::Parser::exception_type&) {
      throw InvalidFormulaException(formula);
    }
}

double FitnessFunctionCalculator::operator()(double x, double y) {
	x_ = x;
	y_ = y;
    return calculator_.Eval();
}

} // namespace common
