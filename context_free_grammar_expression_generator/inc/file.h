#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <type_traits>
#include <stdexcept>
#include "config.h"

template <typename T> class File {
public:
  File(const char *fileName);
  ~File();
  bool readline(char *line);
  template <typename... Args>
  bool write(const char *format, Args... args);

private:
  T file;
};

template <typename T>
File<T>::File(const char *fileName) {
  try {
    if constexpr (std::is_same<T, std::ifstream>::value) {
            file.open(fileName, std::ios::in); // Input mode
        } else if constexpr (std::is_same<T, std::ofstream>::value) {
            file.open(fileName, std::ios::out); // Output mode
        } else {
            throw std::runtime_error("Unsupported file type");
        }
  } catch (typename T::failure e) {
    std::cerr << "Exception opening/reading file";
  }
}

template <typename T>
File<T>::~File() {
  file.close();
}

template <typename T>
bool File<T>::readline(char *line) {
  bool response = false;
  memset(line, 0, sizeof(line));

  file.get(line[0]);
  for (int i = 0; (file.peek() != '\n' && file.peek() != '\0' && file.get(line[i])); i++);
  response = true;

  return response;
}

template <typename T>
template <typename... Args >
bool File<T>::write(const char *format,Args... args) {
  char buffer[BUFFER_SIZE];
  memset(buffer,0,sizeof(buffer));
  bool response = false;

  snprintf(buffer,sizeof(buffer),format,args...);
  file.write(buffer,strlen(buffer));

  response = true;
  return response;
}