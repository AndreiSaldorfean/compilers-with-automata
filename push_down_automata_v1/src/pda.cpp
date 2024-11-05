#include "pda.h"
#include "config.h"

void Pda::pdaPush(const char *str)
{
    pdaStack.push(str);
}
void Pda::pdaPop()
{
    pdaStack.pop();
}
bool Pda::pdaMove(int location, const char *stackTop)
{
    char buffer[BUFFER_SIZE];
    pdaPush(stackTop);
    std::sprintf(buffer, "%d", location);
    pdaPush(buffer);
    return 1;
}
Pda::Pda()
{
}

bool Pda::pdaReplace(int location)
{
    int actionLocation;
    std::string temp = pdaProductions[location];
    int size = pdaProductionSize[location];
    for(int i=0;i< size;i++){
        pdaPop();
    }
    actionLocation = std::stoi(pdaPeek());
    pdaPush(temp.c_str());
    std::string jumpTemp = jump[actionLocation][pdaPeek()].c_str();
    pdaPush(jumpTemp.c_str());
    return 1;
}

std::string Pda::pdaPeek()
{
    if(pdaStack.empty())return "0";
    return pdaStack.top();
}
/**
    * @brief Analyzes the input symbols with the help of jump table
            and the stack
*/
bool Pda::pdaAnalyze(std::string inputBandTokens[])
{
    std::string status = "";
    int intStatus = 0;
    int j = 0;

    /* Initialize stack*/
    {
        pdaPush("$");
        pdaPush("0");
    }
    for (;;)
    {
        std::string temp = inputBandTokens[j];
        intStatus = std::stoi(pdaPeek());
        std::string status = actions[intStatus][temp];
        switch (status[0])
        {
        case 'd':
            pdaMove(std::stoi(status.substr(1)), inputBandTokens[j].data());
            j++;
            break;
        case 'r':
            pdaReplace(std::stoi(status.substr(1)) - 1);
            break;
        case 'a':
            return 1;
        default:
            return 0;
        }
    }

    return 0;
}