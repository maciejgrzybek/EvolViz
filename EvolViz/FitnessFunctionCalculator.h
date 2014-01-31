#pragma once
#include <string>
#include <mu/muParser.h>

namespace common {

class FitnessFunctionCalculator
{
public:
	class InvalidFormulaException : public std::exception {
	public:
		InvalidFormulaException(const std::string& formula);
		virtual const char* what() const throw();
		const std::string& formula();

	private:
		const std::string formula_;
		const std::string error_mgs_;
	};

	FitnessFunctionCalculator(const std::string& formula);
	double operator()(double x, double y);

private:
	double x_;
	double y_;
    std::string formula_;
    mu::Parser calculator_;
};

} // namespace common
