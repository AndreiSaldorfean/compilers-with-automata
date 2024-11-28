#pragma once
#include <vector>
#include <string>
#include <unordered_map>

typedef struct{
    std::string lhs;
    std::vector<std::string> rhs;
}production_t;

typedef struct
{
    std::string startSymbol;
    std::vector<std::string> terminals;
    std::vector<std::string> nonTerminals;
    std::vector<production_t> productions;
}grammar_t;

typedef struct
{
    production_t production;
    std::vector<std::string> lookAhead;
    int dotPos = 0;
}item_t;


typedef struct
{
    std::vector<item_t> items;
    std::vector<std::string> transitions;
}state_t;

typedef struct
{
    std::unordered_map<int,state_t> states;
}dfa_t;
