#pragma once
#include "typedefs.h"
#include <vector>

class Parsable
{
protected:
    grammar_t grammar;
    virtual void closure(item_t, std::vector<item_t>&) = 0;
    virtual std::vector<item_t> goto_(item_t, std::string&) = 0;
    virtual std::vector<std::string> first(std::vector<std::string>) = 0;
    virtual std::vector<std::string> follow(std::vector<std::string>) = 0;
};
