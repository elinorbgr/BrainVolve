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
        // these labels have not been parsed
        std::string::const_iterator a = s.begin(), b = s.end();
        auto parsed = parse_neuron_label(a, b);
        inputs.push_back(neural::Neuron::input_neuron());
        input_labels.push_back(parsed.first);
    }
    for(std::string s : hard_outputs)
    {
        // same here
        std::string::const_iterator a = s.begin(), b = s.end();
        auto parsed = parse_neuron_label(a, b);
        neural::Neuron tmp = neural::Neuron(af_from_gene(parsed.first[0]));
        tmp.set_bias(parsed.second / 100.0);
        outputs.push_back(std::move(tmp));
        output_labels.push_back(parsed.first);
    }
    // dispatchers:
    auto neuron_dispatcher = [&inputs, &outputs, &internals] (neuron_kind kind) -> std::vector<neural::Neuron>& {
        switch(kind)
        {
            case neuron_kind::input_ampl:
            case neuron_kind::input_dir:
                return inputs;
            case neuron_kind::output:
                return outputs;
            default:
                return internals;
        }
    };
    auto label_dispatcher = [&input_labels, &output_labels, &internal_labels] (neuron_kind kind) -> std::vector<std::string>& {
        switch(kind)
        {
            case neuron_kind::input_ampl:
            case neuron_kind::input_dir:
                return input_labels;
            case neuron_kind::output:
                return output_labels;
            default:
                return internal_labels;
        }
    };
    // now extract neuron from genome
    auto neuron_labels = neurons_from_genome(genome);
    for (auto n : neuron_labels)
    {
        neuron_kind kind = kind_from_gene(n.first[0]);
        int index = index_of(n.first, label_dispatcher(kind));
        if(index == -1)
        {
            label_dispatcher(kind).push_back(n.first);
            if(kind == neuron_kind::input_ampl || kind == neuron_kind::input_dir)
            {
                inputs.push_back(neural::Neuron::input_neuron());
                if(kind == neuron_kind::input_ampl)
                    m_input_channels.push_back(n.second);
                else
                    m_input_channels.push_back(-n.second);
            }
            else
            {
                neural::Neuron tmp = neural::Neuron(af_from_gene(n.first[0]));
                if(kind == neuron_kind::output)
                    m_output_channels.push_back(n.second);
                else
                    tmp.set_bias(n.second / 100.0);
                neuron_dispatcher(kind).push_back(std::move(tmp));
            }

        }
        else
        {
            neuron_dispatcher(kind)[index].set_bias(n.second / 100.0);
        }
    }
    // now extract links
    auto links = links_from_genome(genome);
    for(auto l : links)
    {
        neural::Neuron *neuronptr[2] = {nullptr, nullptr};
        // 'from' and 'to' neuron are handled the same way :
        for(int n = 0; n<2; n++)
        {
            std::string label = (n == 0 ? l.first.first : l.first.second );
            unsigned int best = 0;
            size_t i = 0;
            neuron_kind kind = kind_from_gene(label[0]);
            for(auto s : label_dispatcher(kind))
            {
                unsigned int pr = prefix_level(label, s);
                if(pr > best)
                {
                    neuronptr[n] = &neuron_dispatcher(kind)[i];
                    best = pr;
                }
                ++i;
            }
        }
        if(neuronptr[0] == nullptr || neuronptr[1] == nullptr)
            continue;
        (*(neuronptr[1])).link(*(neuronptr[0]), l.second / 100.0);
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

std::vector<int> Brain::get_input_channels()
{
    return m_input_channels;
}

std::vector<int> Brain::get_output_channels()
{
    return m_output_channels;
}
