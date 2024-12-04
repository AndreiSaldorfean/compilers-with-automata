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

#if defined(DEBUG_MACRO)
void log(int x){
  char buffer[20];
  snprintf(buffer,sizeof(buffer),"%d",x);
  printf("%s\n",buffer);
}
void log(const char* ch){
  printf("%s\n",ch);
}
void log(std::string str){
  printf("%s\n",str.data());
}

void log(std::vector<std::string> arr){
  for(auto str:arr){
    printf("%s ",str.data());
  }
  printf("\n");
}
#endif