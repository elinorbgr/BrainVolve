#include <cctype>

#include "parser.hpp"

bool is_valid_genom(std::string str)
{
    for(char c : str)
        if((!isalnum(c)) && c != '-' && c != '+')
            return false;
    return true;
}
