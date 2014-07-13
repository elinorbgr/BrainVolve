#include "neural/neuron.hpp"

/*
 * Neuron Class implementation
 */

// Constructors

neural::Neuron::Neuron(const neural::activation_func &afunc):
    m_ineuron(new NeuronData(afunc))
{
}

neural::Neuron neural::Neuron::input_neuron()
{
    return Neuron(neural::af::zero);
}

// Getters

double neural::Neuron::get_bias() const
{
    return m_ineuron->bias;
}

double neural::Neuron::get_value() const
{
    return m_ineuron->value;
}

// Setters

void neural::Neuron::set_rate(double rate)
{
    m_ineuron->rate = rate;
}

void neural::Neuron::set_value(double value)
{
    m_ineuron->value = value;
}

void neural::Neuron::set_bias(double bias)
{
    m_ineuron->bias = bias;
}

void neural::Neuron::add_error(double error)
{
    m_ineuron->error_buffer += error;
}

// Use

void neural::Neuron::link(Neuron &from, double weight)
{
    m_ineuron->inputs.push_back(std::make_pair(from.m_ineuron.get(), weight));
}

void neural::Neuron::compute()
{
    double x = m_ineuron->bias;
    for( auto p : m_ineuron->inputs )
    {
        x += p.second * p.first->value;
    }
    m_ineuron->value_buffer = m_ineuron->afunc->first(x);
    double e = m_ineuron->error * m_ineuron->afunc->second(x);
    m_ineuron->bias += e * m_ineuron->rate;
    for( auto &p : m_ineuron->inputs )
    {
        p.first->error_buffer += p.second * e;
        p.second += e * p.first->value * m_ineuron->rate;
    }
}

void neural::Neuron::sync()
{
    m_ineuron->value = m_ineuron->value_buffer;
    m_ineuron->value_buffer = 0.0;
    m_ineuron->error = m_ineuron->error_buffer;
    m_ineuron->error_buffer = 0.0;
}
