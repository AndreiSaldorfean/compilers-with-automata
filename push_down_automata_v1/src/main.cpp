/*
  OBS: - Nu merge pentru paranteze din cauza ca nu am implementat matricea de precedenta
       - Pentru paranteze cate elemente trebuie scoase din stiva (linia 123 din compiler.cpp)?

  Probleme pe care le aveam data trecuta:
    - Am avut cateva intrari in tabla de actiune gresite
    - Nu citeam input-ul bine (problema cu memcpy(band,argv[1],sizeof(BUFFER_SIZE))) linia 25
    - Nu trebuia sa modific actiunea de pop pentru paranteze
*/
#include "compiler.h"
#include "typedefs.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
  Compiler compiler;
  inputBand_t *band = new inputBand_t[BUFFER_SIZE];
  memset(band,0,BUFFER_SIZE);
  bool status = 0;

  if(argc < 2){
    std::cerr<<"Please provide an input string!\n";
    return 1;
  }else{
    memcpy(band,argv[1],BUFFER_SIZE-1);
  }

  /*Input: grammar,actions table, goto table and input string*/
  {
    compiler.parseGrammer("resources/grammar.txt");
    compiler.parseActions("resources/actions.txt");
    compiler.parseJump("resources/goto.txt");
  }

  status = compiler.analyzeLine(band);
  if(status)printf("Sucess\n");
  else printf("Fail");
  delete[] band;
  return !status;
}
