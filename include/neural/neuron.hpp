#ifndef NEURAL_NEURON_HPP
#define NEURAL_NEURON_HPP

#include <vector>

#include "neural/activationfuncs.hpp"

namespace neural
{

/**
 * Class representing a Neuron.
 */

class Neuron
{
    private:
        double m_value;
        double m_error;
        double m_value_buffer;
        double m_error_buffer;
        double m_bias;
        const activation_func *m_afunc;
        std::vector<std::pair<Neuron*,double> > m_inputs;

    public:
        // builders
        Neuron(const activation_func *afunc);

        // getters
        double get_bias() const;
        double get_value() const;

        // setters
        void set_value(double value);
        void set_bias(double bias);
        void add_error(double error);

        // use
        void link(Neuron* from, double weight);
        void compute();
        void sync();

        // special cases
        static Neuron input_neuron();
};

} // namespace neural

#endif // NEURAL_NEURON_HPP
