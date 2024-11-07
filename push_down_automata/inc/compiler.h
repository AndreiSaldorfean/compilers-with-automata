#pragma once
#include "config.h"
#include <string>
#include <unordered_map>
#include "pda.h"

class Compiler : Pda {
  std::string startSymbol;
  std::string terminals[MAX_GRAMMER_LENGTH];
  std::string nonTerminals[MAX_GRAMMER_LENGTH];
  std::unordered_map<std::string, std::string[MAX_PRODUCTIONS_TOKENS]> productions;


public:
  Compiler();
  bool parseGrammer(const char *fileName);
  bool parseActions(const char *fileName);
  bool parseJump(const char *fileName);
  bool parseStrings(const char *fileName);
  void printGrammer();
  void parseExpression(const char *fileName);
  void generateRandomExpression();
  bool analyzeLine(const char* input);
};
