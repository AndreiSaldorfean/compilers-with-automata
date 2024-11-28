#include "utils.h"
#include <string.h>

std::vector<std::string> tokenize(char* string, const char* delimiter){
   std::vector<std::string> out;
   char* token = strtok(string, delimiter);
   out.reserve(20);

   for(;token != nullptr;){
      out.emplace_back(token);
      token = strtok(nullptr,delimiter);
   }
   return out;
}