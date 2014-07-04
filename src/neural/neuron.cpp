#include "neural/neuron.hpp"

/*
 * Neuron class impementation.
 */

// Constructor

neural::Neuron::Neuron(const neural::activation_func *afunc):
    m_afunc(afunc)
{
}

// Getters

double neural::Neuron::get_bias() const
{
    return m_bias;
}

double neural::Neuron::get_value() const
{
    return m_value;
}

// Setters

void neural::Neuron::set_value(double value)
{
    m_value = value;
}

void neural::Neuron::set_bias(double bias)
{
    m_bias = bias;
}

void neural::Neuron::add_error(double error)
{
    m_error_buffer += error;
}

// Use

void neural::Neuron::link(Neuron* from, double weight)
{
    m_inputs.push_back(std::make_pair(from, weight));
}

void neural::Neuron::compute()
{
    double x = m_bias;
    for( auto p : m_inputs )
    {
        x += p.second * p.first->get_value();
    }
    m_value_buffer = m_afunc->first(x);
    double e = m_error * m_afunc->second(x);
    m_bias += e;
    for( auto p : m_inputs )
    {
        p.first->add_error(p.second * e);
        p.second += e * p.first->get_value();
    }
}

void neural::Neuron::sync()
{
    m_value = m_value_buffer;
    m_value_buffer = 0.0;
    m_error = m_error_buffer;
    m_error_buffer = 0.0;
}

neural::Neuron neural::Neuron::input_neuron()
{
    return Neuron(&neural::af::zero);
}

