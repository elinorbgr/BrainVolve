#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include <vector>

#include "neural/neuron.hpp"

namespace neural
{

/**
 * Class representing a Network.
 * Encapsulates a built network for use.
 */

class Network
{
    private:
        std::vector<Neuron> m_input_neurons;
        std::vector<Neuron> m_internal_neurons;
        std::vector<Neuron> m_output_neurons;

    public:
        // give neurons to the network
        void emplace_input_neuron(Neuron &n);
        void emplace_input_neurons(std::vector<Neuron> &ns);
        void emplace_internal_neuron(Neuron &n);
        void emplace_internal_neurons(std::vector<Neuron> &ns);
        void emplace_output_neuron(Neuron &n);
        void emplace_output_neurons(std::vector<Neuron> &ns);
        // running the network
        void set_inputs(std::vector<double> inputs);
        std::vector<double> get_outputs();
        void add_errors(std::vector<double> errors);
        void step();
};

} // namespace neural

#endif // NEURAL_NETWORK_HPP
