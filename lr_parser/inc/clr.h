#include "parsable.h"
#include "typedefs.h"
#include <unordered_map>

class Clr : Parsable
{
    std::unordered_map<std::string,std::unordered_map<int,std::string>> actionsTable;
    std::unordered_map<std::string,std::unordered_map<int,int>> gotoTable;

    void constructGotoGraph();

    virtual std::vector<item_t> goto_(item_t, std::string&);
    virtual void closure(item_t, std::vector<item_t>&);
    virtual std::vector<std::string> first(std::vector<std::string>);
    virtual std::vector<std::string> follow(std::vector<std::string>);
public:
    void constructDFA();
    void setGrammar(grammar_t);
    void constructActionsTable();
    void constructGotoTable();
};
