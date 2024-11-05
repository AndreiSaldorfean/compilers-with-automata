#include "compiler.h"
#include "rng.h"

int main() {
  Complier compiler;
  Rng rng(31452452536ULL, 0, 2502456239ULL);

  compiler.parse_grammer("../resources/grammar.txt");
  compiler.generate_random_expression([&](){return rng.generate();});

  return 0;
}
