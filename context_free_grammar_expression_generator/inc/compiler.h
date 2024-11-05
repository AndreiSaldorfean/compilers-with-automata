#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include "config.h"
#include <functional>

class Complier{
private:
  char startSymbol;
  char terminals[MAX_GRAMMER_LENGTH];
  char nonTerminals[MAX_GRAMMER_LENGTH];
  std::unordered_map<char,std::string[MAX_PRODUCTIONS_TOKENS]> productions;
public:
  Complier();
  bool parse_grammer(const char *fileName);
  void print_grammer();
  void parse_expression(const char *fileName);
  void generate_random_expression(std::function<int64_t()> rng, bool printSteps = 0);
};
