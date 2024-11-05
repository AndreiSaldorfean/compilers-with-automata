#pragma once
#include <stack>
#include <string>
#include <unordered_map>
#include "typedefs.h"
#include "config.h"

class Pda
{
  std::stack<std::string> pdaStack;

protected:
  std::string pdaProductions[BUFFER_SIZE];
  int pdaProductionSize[BUFFER_SIZE];
  std::unordered_map<int, std::unordered_map<std::string, std::string>> actions;
  std::unordered_map<int, std::unordered_map<std::string, std::string>> jump;

protected:
  Pda();
  void pdaPush(const char* str);
  void pdaPop();
  std::string pdaPeek();
  bool pdaMove(int location,const char* stackTop);
  bool pdaReplace(int location);
  bool pdaAnalyze(std::string inputBandTokens[]);
};