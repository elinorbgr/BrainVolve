#include "neural/activationfuncs.hpp"

#include <cmath>

/*
 * F (x) = 0
 * F'(x) = 0
 */
const neural::activation_func neural::af::zero (
    [] (double) -> double { return 0.0; },
    [] (double) -> double { return 0.0; }
);

/*
 * F (x) = U(x) (step function at 0)
 * F'(x) = 0
 */
const neural::activation_func neural::af::step(
    [] (double x) -> double { return x>=0.0 ? 1.0 : 0.0; },
    [] (double) -> double { return 0.0; }
);

/*
 * F (x) = x
 * F'(x) = 1
 */
const neural::activation_func neural::af::linear(
    [] (double x) -> double { return x; },
    [] (double) -> double { return 1.0; }
);

/*
 * F (x) = 1 / ( 1 + e^(-x) )
 * F'(x) = e^(-x) / ( 1 + e^(-x))^2
 */
const neural::activation_func neural::af::sigmoid(
    [] (double x) -> double { return 1.0 / (1.0 + std::exp(-x)); },
    [] (double x) -> double {
        double expx = std::exp(-x);
        return expx / std::pow(1.0 + expx, 2);
    }
);

/*
 * F (x) = tanh(x)
 * F'(x) = 1 - tanh(x)^2
 */
const neural::activation_func neural::af::tanh(
    [] (double x) -> double { return std::tanh(x); },
    [] (double x) -> double { return 1.0 - std::pow(std::tanh(x),2); }
);

