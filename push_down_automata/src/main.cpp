/*
  Probleme pe care le aveam data trecuta:
    - Am avut cateva intrari in tabla de actiune gresite
    - Nu citeam input-ul bine (problema cu memcpy(band,argv[1],sizeof(BUFFER_SIZE))). Solutie: trimit direct "argv" catre "analyzeLine"
    - Nu trebuia sa modific actiunea de pop pentru paranteze
*/
#include "compiler.h"
#include "typedefs.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
  Compiler compiler;
  bool status;

  if(argc < 2){
    std::cerr<<"Please provide an input string!\n";
    return 1;
  }

  /*Input: grammar,actions table, goto table and input string*/
  {
    compiler.parseGrammer("resources/grammar.txt");
    compiler.parseActions("resources/actions.txt");
    compiler.parseJump("resources/goto.txt");
  }

  status = compiler.analyzeLine(argv[1]);
  if(status)printf("Sucess\n");
  else printf("Fail");
  return !status;
}
