#include "file.h"
#include "utils.h"
#include "typedefs.h"
#include "clr.h"

using namespace std;

int main(int argc,char** argv) {
    Clr clr;

    /* Read the grammar */
    {
        grammar_t grammar;
        File<std::ifstream> fin(argv[1]);
        std::vector<std::string> stringArrayBuffer;
        std::vector<std::string> tokenizedLine;
        production_t productionBuffer;
        std::string stringBuffer;

        stringArrayBuffer.reserve(20);
        tokenizedLine.reserve(20);

        char* line = new char[BUFFER_SIZE];

        /* Read start symbol*/
        fin.readline(line);
        grammar.startSymbol = line;

        /* Read terminals*/
        fin.readline(line);
        grammar.terminals = tokenize(line, " ");

        /* Read non-terminals*/
        fin.readline(line);
        grammar.nonTerminals = tokenize(line, " ");

        for(;fin.readline(line);){
            tokenizedLine = tokenize(line," ");
            for(int i=1;i<tokenizedLine.size();i++){
                stringArrayBuffer.emplace_back(tokenizedLine[i]);
            }
            productionBuffer.lhs = tokenizedLine[0];
            productionBuffer.rhs = stringArrayBuffer;

            grammar.productions.emplace_back(productionBuffer);
        }
        clr.setGrammar(grammar);

        delete[] line;
    }

    clr.constructDFA();
    return 0;
}
