#include "utils/MathUtils.h"

double MathUtils::add(double a, double b) { return a + b; }
double MathUtils::sub(double a, double b) { return a - b; }
double MathUtils::mul(double a, double b) { return a * b; }
double MathUtils::div(double a, double b) { return b != 0 ? a / b : 0; }
