#include "Population.h"
namespace model {

bool Population::Subject::operator< (const Subject& other) { return value <  other.value; }
bool Population::Subject::operator==(const Subject& other) { return value == other.value; }
bool Population::Subject::operator<=(const Subject& other) { return value <= other.value; }
bool Population::Subject::operator> (const Subject& other) { return value >  other.value; }
bool Population::Subject::operator>=(const Subject& other) { return value >= other.value; }
bool Population::Subject::operator!=(const Subject& other) { return value != other.value; }

} // namespace model