#include "brain.hpp"
#include "parser.hpp"

unsigned int prefix_level(const std::string &str, const std::string &prefix)
{
    // returns prefix.size() if prefix prefixes str, O otherwise
    if(str.size() < prefix.size())
        return 0;
    auto it = str.begin();
    for(char c : prefix)
    {
        if(c != *it)
            return 0;
        ++it;
    }
    return prefix.size();
}

// some helper functions for the constructor
int index_of(std::string str, const std::vector<std::string> &vec)
{
    int i = 0;
    for (auto s : vec)
    {
        if(s == str)
            return i;
        ++i;
    }
    return -1;
}

Brain::Brain(std::string genome,
             const std::vector<std::string> &hard_inputs,
             const std::vector<std::string> &hard_outputs)
{
    m_hard_input_count = hard_inputs.size();
    m_hard_output_count = hard_outputs.size();

    std::vector<neural::Neuron> inputs;
    std::vector<std::string> input_labels;
    std::vector<neural::Neuron> internals;
    std::vector<std::string> internal_labels;
    std::vector<neural::Neuron> outputs;
    std::vector<std::string> output_labels;
    // first get hard data
    for(std::string s : hard_inputs)
    {
        inputs.push_back(neural::Neuron::input_neuron());
        input_labels.push_back(s);
    }
    for(std::string s : hard_outputs)
    {
        outputs.push_back(neural::Neuron(af_from_gene(s[0])));
        output_labels.push_back(s);
    }
    // now extract neuron from genome
    auto neuron_labels = neurons_from_genome(genome);
    for (auto n : neuron_labels)
    {
        int index;
        switch(kind_from_gene(n.first[0]))
        {
            case neuron_kind::input:
                index = index_of(n.first, input_labels);
                if (index == -1)
                {
                    input_labels.push_back(n.first);
                    inputs.push_back(neural::Neuron(af_from_gene(n.first[0])));
                    m_input_channels.push_back(n.second);
                }
                break;
            case neuron_kind::output:
                index = index_of(n.first, output_labels);
                if (index == -1)
                {
                    output_labels.push_back(n.first);
                    outputs.push_back(neural::Neuron(af_from_gene(n.first[0])));
                    m_output_channels.push_back(n.second);
                }
                else
                {
                    outputs[index].set_bias(n.second / 100.0);
                }
                break;
            default:
                index = index_of(n.first, internal_labels);
                if (index == -1)
                {
                    internal_labels.push_back(n.first);
                    neural::Neuron tmp = neural::Neuron(af_from_gene(n.first[0]));
                    tmp.set_bias(n.second / 100.0);
                    internals.push_back(std::move(tmp));
                }
                else
                {
                    internals[index].set_bias(n.second / 100.0);
                }
        }
    }
    // now extract links
    auto links = links_from_genome(genome);
    for(auto l : links)
    {
        neural::Neuron *from = nullptr;
        neural::Neuron *to = nullptr;
        unsigned int best_from;
        unsigned int best_to;
        size_t i = 0;
        // search in inputs
        for(auto s : input_labels)
        {
            unsigned int pr = prefix_level(l.first.first, s);
            if(pr > best_from)
            {
                from = &inputs[i];
                best_from = pr;
            }
            pr = prefix_level(l.first.second, s);
            if(pr > best_to)
            {
                to = &inputs[i];
                best_to = pr;
            }
            ++i;
        }
        i = 0;
        for(auto s : output_labels)
        {
            unsigned int pr = prefix_level(l.first.first, s);
            if(pr > best_from)
            {
                from = &outputs[i];
                best_from = pr;
            }
            pr = prefix_level(l.first.second, s);
            if(pr > best_to)
            {
                to = &outputs[i];
                best_to = pr;
            }
            ++i;
        }
        i = 0;
        for(auto s : internal_labels)
        {
            unsigned int pr = prefix_level(l.first.first, s);
            if(pr > best_from)
            {
                from = &internals[i];
                best_from = pr;
            }
            pr = prefix_level(l.first.second, s);
            if(pr > best_to)
            {
                to = &internals[i];
                best_to = pr;
            }
            ++i;
        }
        if(from == nullptr || to == nullptr)
            continue;
        (*to).link(*from, l.second / 100.0);
    }
    // network is build, store it now
    m_net.emplace_input_neurons(inputs);
    m_net.emplace_internal_neurons(internals);
    m_net.emplace_output_neurons(outputs);

}

std::vector<double> Brain::answer(std::vector<double> inputs)
{
    while(inputs.size() < m_hard_input_count + m_input_channels.size())
        inputs.push_back(0.0);
    m_net.set_inputs(inputs);
    m_net.step();
    return m_net.get_outputs();
}

void Brain::punish(std::vector<double> errors)
{
    while(errors.size() < m_hard_output_count + m_output_channels.size())
        // fill with zeros
        errors.push_back(0.0);
    m_net.add_errors(errors);
    // force acknowledgement
    m_net.step();
}

std::vector<size_t> Brain::get_input_channels()
{
    return m_input_channels;
}

std::vector<size_t> Brain::get_output_channels()
{
    return m_output_channels;
}
