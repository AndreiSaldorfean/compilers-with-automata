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
#endif
