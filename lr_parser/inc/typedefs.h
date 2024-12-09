#pragma once
#include <vector>
#include <string>
#include <cstring>

typedef struct production_t
{
    std::string lhs;
    std::vector<std::string> rhs;
    // Equality operator
    bool operator==(const production_t& other) const {
      bool isEqual;
      return lhs == other.lhs &&
             rhs == other.rhs;
    }
#ifdef DEBUG_MACRO
    char debugger[10];
    void initDebugger(){
      memset(debugger,0,sizeof(debugger));
      memcpy(debugger,lhs.data(),lhs.size());
      debugger[lhs.size()] = '-';
      debugger[lhs.size()+1] = '>';
      std::string buffer;
      for(std::string str : rhs){
        buffer+=str;
      }
      memcpy(debugger+lhs.size()+2,buffer.data(),buffer.size());
    }
    void print(){
      printf("%s\n",debugger);
    }
#endif
}production_t;

typedef struct item_t
{
    production_t production;
    std::vector<std::string> lookAhead;
    int dotPos = 0;

    // Equality operator
    bool operator==(const item_t& other) const {
        return production == other.production &&
               lookAhead == other.lookAhead &&
               dotPos == other.dotPos;
    }

#ifdef DEBUG_MACRO
    char debugger[20];
    void initDebugger(){
      production.initDebugger();
      std::string buffer;
      std::string buffer2;
      int i=0;

      memset(debugger,0,sizeof(debugger));
      memcpy(debugger,production.debugger,sizeof(debugger));
      buffer2 = debugger;
      buffer2.insert(buffer2.begin()+buffer2.find(">")+1+dotPos,1,'.');
      memcpy(debugger,buffer2.data(),buffer2.size());

      for(i=0;(debugger[i]!=0);i++);

      memcpy(debugger+i," ",1);

      for(auto str:lookAhead)buffer+=str;
      memcpy(debugger+i+1,buffer.data(),buffer.size());
    }
    void print(const char terminator=0){
      char format[5] = {"%s"};
      format[2] = terminator;
      printf(format,debugger);
    }
#endif
}item_t;

typedef struct grammar_t
{
    std::string startSymbol;
    std::vector<std::string> terminals;
    std::vector<std::string> nonTerminals;
    std::vector<production_t> productions;

#ifdef DEBUG_MACRO
    char debugger[11][11];
    void initDebugger(){
      std::string buffer;
      memset(debugger,0,sizeof(debugger));
      memcpy(debugger[0],startSymbol.data(),startSymbol.size());
      for(auto str: terminals)buffer+=str;
      memcpy(debugger[1],buffer.data(),buffer.size());
      buffer.clear();
      for(auto str: nonTerminals)buffer+=str;
      memcpy(debugger[2],buffer.data(),buffer.size());
      int i=3;
      for(auto production : productions){
        memcpy(debugger[i++],production.debugger,sizeof(production.debugger));
      }
    }
    void print(){
      for(int i=0;i<11;i++){
        printf("%s\n",debugger[i]);
      }
    }
#endif
}grammar_t;

