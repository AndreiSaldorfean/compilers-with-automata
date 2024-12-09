#pragma once
#include <string.h>
#include <string>
#include <vector>

std::vector<std::string> tokenize(char* string, const char* delimiter);


#if defined(DEBUG_MACRO)
void log(int x);
void log(const char* ch);
void log(std::string str);
void log(std::vector<std::string> arr);

#define COPY(dest,src)\
    memset(dest,0,sizeof(dest));\
    for(auto str: src){\
        memcpy(dest,str.data(),str.size());\
    }

#endif
