#include "parsable.h"
#include "typedefs.h"
#include "unordered_map"

class Clr : Parsable
{
    dfa_t dfa;
    std::vector<std::vector<std::string>> actionsTable;
    std::vector<std::vector<std::string>> gotoTable;
    std::unordered_map<int,std::unordered_map<std::string,int>> transition;

    virtual std::vector<item_t> goto_(item_t);
    virtual std::vector<item_t> closure(item_t);
    virtual std::vector<std::string> first(std::vector<std::string>);
    virtual std::vector<std::string> follow(std::vector<std::string>);
public:
    void constructDFA();
    void setGrammar(grammar_t);
    std::vector<std::vector<std::string>> constructActionsTable(std::vector<item_t>);
    std::vector<std::vector<std::string>> constructGotoTable(std::vector<item_t>);
};
