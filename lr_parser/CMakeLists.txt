set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.14)
project(SimpleGrammer)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/out)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(main ${SOURCES})
target_include_directories(main PRIVATE ./inc ./libs/)
