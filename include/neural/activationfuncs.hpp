#ifndef NEURAL_ACTIVATIONFUNCS_HPP
#define NEURAL_ACTIVATIONFUNCS_HPP

#include <functional>
#include <utility>

namespace neural
{

/**
 * Set of available activation functions.
 * Described as pairs of 2 std::functions :
 *   - the first returns the value of the function at input point
 *   - the second returns the value of the derivated of the function at input point
 * Both are double -> double
 */

namespace af
{

typedef std::pair<
    const std::function<double(double)>,
    const std::function<double(double)>
> activation_func;

extern const activation_func zero;

extern const activation_func step;

extern const activation_func linear;

extern const activation_func sigmoid;

extern const activation_func tanh;

}

} // namespace neural
#endif //NEURAL_ACTIVATIONFUNCS_HPP
