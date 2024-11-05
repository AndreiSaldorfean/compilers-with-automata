# Automata and compilers
## Requirements

- CMake
- Make


This are the automata I had to implement. I picked c++ because I wanted to practice it together with CMake.

To build any of the project run:
`````
cd <project>
cmake -S . -B build -G "Unix Makefiles"
`````
or
`````
cd <project>
make
`````
I made a Makefile that runs the cmake command, I plan on shifting to a more traditional approach by using a scripting language instead of a build system to call lengthy commands :D

*Note: The executable is always located in `build/bin/main.exe`*