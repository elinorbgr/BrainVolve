#ifndef NEURAL_NEURON_HPP
#define NEURAL_NEURON_HPP

#include <memory>
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
        struct NeuronData
        {
            double value;
            double error;
            double value_buffer;
            double error_buffer;
            double bias;
            double rate;
            const activation_func *afunc;
            std::vector<std::pair<NeuronData*,double> > inputs;
            NeuronData(const activation_func &afunc):rate(1.0),afunc(&afunc){}
        };
        std::unique_ptr<NeuronData> m_ineuron;

    public:
        // builders
        Neuron(const activation_func &afunc);

        // getters
        double get_bias() const;
        double get_value() const;

        // setters
        void set_rate(double rate);
        void set_value(double value);
        void set_bias(double bias);
        void add_error(double error);

        // use
        void link(Neuron &from, double weight);
        void compute();
        void sync();

        // special cases
        static Neuron input_neuron();
};

} // namespace neural

#endif // NEURAL_NEURON_HPP
