set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.14)
project(SimpleGrammerTests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB SOURCES "src/*.cpp" "../src/compiler.cpp" "../src/pda.cpp")
add_executable(
  main
  ${SOURCES}
)
target_include_directories(main PRIVATE ./inc ./libs/ ../inc/ ../src)
target_link_libraries(
  main
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main)