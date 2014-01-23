#include "evol/EvolFunctions.hpp"
#include "Model.h"
#include <thread>
#include <iostream>
#include <gsl/gsl_rng.h>

int main() {
	Model model;
	//std::thread(std::ref(model));
	evol::EvolFunctions::initializeGSL();
	std::cout << "Gauss: " << evol::EvolFunctions::gaussRandom(0, 3) << std::endl;
}