#ifndef ALIFE_PARSER_HPP
#define ALIFE_PARSER_HPP

#include <string>
#include <utility>
#include <vector>

#include "neural/neuron.hpp"

/*
 * Checks if a genome is ine the correct alphabet :
 * alphanumerix or '-' or '+'
 */
bool is_valid_genom(const std::string &str);

/*
 * Parses a single neuron
 */

std::pair<std::string, unsigned int> parse_neuron_label(std::string::const_iterator &from, std::string::const_iterator &endit);

/*
 * Returns a vector of (label, value) descritpion of neurons
 * defined in this genome. Assumes is_valid_genom(str) is true.
 * Undefined behaviour if this requirement is not met.
 */

std::vector<std::pair<std::string, unsigned int> > neurons_from_genome(const std::string &str);

/*
 * Returns a vector of ((label_from, label_to), weight) description of neuron connections
 * defined in this genome. Assumes is_valid_genom(str) is true.
 * Undefined behavious if this requirement is not met.
 */

std::vector<std::pair<std::pair<std::string, std::string>, int> > links_from_genome(const std::string &str);

/*
 * Returns the activation function depending of special char
 */

const neural::activation_func* af_from_gene(char c);

enum class neuron_kind { input_ampl, input_dir, output, internal };

neuron_kind kind_from_gene(char c);

#endif // ALIFE_PERSER_HPP
