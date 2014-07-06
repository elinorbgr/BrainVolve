#ifndef ALIFE_BRAIN_HPP
#define ALIFE_BRAIN_HPP

#include <string>
#include <vector>

#include "neural/network.hpp"

class Brain
{
    private:
        neural::Network m_net;
        std::vector<size_t> m_input_channels;
        std::vector<size_t> m_output_channels;
        size_t m_hard_input_count;
        size_t m_hard_output_count;

    public:
        Brain(std::string genome,
              const std::vector<std::string> &hard_inputs,
              const std::vector<std::string> &hard_outputs);
        std::vector<double> answer(std::vector<double> inputs);
        void punish(std::vector<double> errors);
        std::vector<size_t> get_input_channels();
        std::vector<size_t> get_output_channels();
};

#endif // ALIFE_BRAIN_HPP
