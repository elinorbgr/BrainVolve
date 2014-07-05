#include "neural/network.hpp"

/*
 * Class Network implementation
 */

// give neurons to the network

void neural::Network::emplace_input_neuron(Neuron &n)
{
    m_input_neurons.push_back(std::move(n));
}

void neural::Network::emplace_input_neurons(std::vector<Neuron> &ns)
{
    for (auto &n : ns)
        m_input_neurons.push_back(std::move(n));
}

void neural::Network::emplace_internal_neuron(Neuron &n)
{
    m_internal_neurons.push_back(std::move(n));
}

void neural::Network::emplace_internal_neurons(std::vector<Neuron> &ns)
{
    for (auto &n : ns)
        m_internal_neurons.push_back(std::move(n));
}

void neural::Network::emplace_output_neuron(Neuron &n)
{
    m_output_neurons.push_back(std::move(n));
}

void neural::Network::emplace_output_neurons(std::vector<Neuron> &ns)
{
    for (auto &n : ns)
        m_output_neurons.push_back(std::move(n));
}

// running the network

void neural::Network::set_inputs(std::vector<double> inputs)
{
    auto it = inputs.begin();
    for(auto &n : m_input_neurons)
    {
        n.set_value(*it);
        ++it;
    }
}

std::vector<double> neural::Network::get_outputs()
{
    std::vector<double> outs;
    for(auto &n : m_output_neurons)
        outs.push_back(n.get_value());
    return outs;
}

void neural::Network::add_errors(std::vector<double> errors)
{
    auto it = errors.begin();
    for(auto &n : m_output_neurons)
    {
        n.add_error(*it);
        ++it;
    }
}

void neural::Network::step()
{
    for(auto &n : m_internal_neurons)
        n.compute();
    for(auto &n : m_output_neurons)
        n.compute();
    for(auto &n : m_internal_neurons)
        n.sync();
    for(auto &n : m_output_neurons)
        n.sync();
}
