#include <cctype>

#include "parser.hpp"

bool is_valid_genom(std::string str)
{
    for(char c : str)
        if(!(c >= '0' && c <= '9') &&
           !(c >= 'a' && c <= 'z') &&
           !(c >= 'A' && c <= 'Z') &&
             c != '-' && c != '+' )
            return false;
    return true;
}

/*
 * Parses a neuron label between from and endit iterators
 * from is effectively changed to next position after neuron label if label is found
 * if no label is found, iterator remains at firt invalid char
 */

std::pair<std::string, unsigned int> parse_neuron_label(std::string::iterator &from, std::string::iterator &endit)
{
    std::string name = "";
    unsigned int value = 0;
    while(from != endit)
    {
        char c = *from;
        if(c >= 'A' && c <= 'Z')
        {
            name += c;
        }
        else if(c >= '0' && c <= '9')
        {
            value *= 10;
            value += (c - '0');
        }
        else if(c >= 'a' && c <= 'z')
        {
            name += c;
            ++from;
            return std::make_pair(name, value);
        }
        else
        {
            // invalid sequence
            break;
        }
        // iterate
        ++from;
    }
    // there is no valid neuron in this interval
    return std::make_pair("", 0);

}

std::vector<std::pair<std::string, unsigned int> > neurons_from_genome(std::string str)
{
    // A neuron id is in the form :
    // '+(A-Z0-9)*(a-z)'
    std::vector<std::pair<std::string, unsigned int> > neurons;
    for(auto it = str.begin(), endit = str.end(); it != endit;)
    {
        if(*it != '+')
        {
            // not the begining of a neuron
            ++it;
            continue;
        }
        ++it;
        auto neuron = parse_neuron_label(it, endit);
        if(neuron.first.empty())
            continue;
        neurons.push_back(neuron);
    }
    return neurons;
}

std::vector<std::pair<std::pair<std::string, std::string>, int> > links_from_genome(std::string str)
{
    std::vector<std::pair<std::pair<std::string, std::string>, int> > links;
    for(auto it = str.begin(), endit = str.end(); it != endit;)
    {
        if(*it != '-')
        {
            // not the begining of a link
            ++it;
            continue;
        }
        ++it;
        auto neuron1 = parse_neuron_label(it, endit);
        if(neuron1.first.empty())
            continue;
        auto neuron2 = parse_neuron_label(it, endit);
        if(neuron2.first.empty())
            continue;
        links.push_back(std::make_pair(
            std::make_pair(neuron1.first, neuron2.first),
            (int)neuron1.second - (int)neuron2.second));
    }
    return links;
}
