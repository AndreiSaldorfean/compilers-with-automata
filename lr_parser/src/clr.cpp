#include "clr.h"
#include "typedefs.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include "utils.h"

/*==============================================================*/
/*                 Constans and local variables                 */
/*==============================================================*/

/*==============================================================*/
/*                Local functions declaration                   */
/*==============================================================*/

/*==============================================================*/
/*                Local functions definitions                   */
/*==============================================================*/

/*==============================================================*/
/*              Global Parsable Implementation                  */
/*==============================================================*/
std::vector<item_t> Clr::goto_(item_t)
{
    std::vector<item_t> temp;
    return temp;
}

/**
 * @brief Compute closure for an lr item
 *
 * @steps
 *    - Compute FIRST for the paramter
 *    - Add the next lr item (recursive)
 *
 * @param item_t item
 * @return state
 */
std::vector<item_t> Clr::closure(item_t item)
{
    std::vector<std::string> tempString = item.production.rhs;
    std::vector<item_t> state;
    item_t tempItem;
    state.reserve(20);

    // Find all productions that start with the non-terminal that is after dot
    for(production_t production : grammar.productions){
        std::vector<std::string> firstArgs;
        firstArgs.reserve(20);

      if(tempString[item.dotPos] == production.lhs){
        tempItem.production = production;

        /*compute first*/
        {
            /*prepare the first arguments*/
            for(int i=item.dotPos+1;i<tempString.size();i++){
                firstArgs.emplace_back(tempString[i]);
            }
            for(std::string symbol : item.lookAhead){
                firstArgs.emplace_back(symbol);
            }

            tempItem.lookAhead = first(firstArgs);
#if defined(DEBUG_MACRO)
            tempItem.initDebugger();
            tempItem.print('\n');
#endif
        }

        state.emplace_back(tempItem);
      }

    }
    return state;
}

std::vector<std::string> Clr::first(std::vector<std::string> symbols)
{
    std::vector<std::string> temp;
    temp.reserve(20);
    for(std::string symbol:symbols){

        if(std::find(grammar.nonTerminals.begin(),grammar.nonTerminals.end(),symbol) != grammar.nonTerminals.end()){
            std::vector<std::string> firstArgs;
            firstArgs.reserve(20);

            /*prepare the first arguments*/
            for(production_t production : grammar.productions){
                if(production.lhs == symbol){
                    for(std::string str : production.rhs){
                        firstArgs.emplace_back(str);
                    }
                    for(std::string str : first(firstArgs)){
                        temp.emplace_back(str);
                    }
                }
            }
        }else{
            temp.emplace_back(symbol);
        }
        return temp;

    }
    return temp;

}

std::vector<std::string> Clr::follow(std::vector<std::string> symbols)
{
    std::vector<std::string> temp;
    return temp;
}

/*==============================================================*/
/*                Global CLR Implementation                     */
/*==============================================================*/

void Clr::setGrammar(grammar_t grammar)
{
    this->grammar = grammar;
}

void Clr::constructDFA()
{
    /*
        Note:
            - By design the dot is already added for each LR(1) item, see item_t struct.
            - That will result in one less step for the initial I0 state.
    */

    // Augment the grammar
    {
        std::vector<std::string> temp;
        temp.reserve(1);
        temp.emplace_back(grammar.productions[0].lhs);

        production_t newProduction =
        {
            /*Lhs*/ grammar.productions[0].lhs + "'",
            /*Rhs*/ temp
        };
#if defined(DEBUG_MACRO)
        newProduction.initDebugger();
#endif

        /*Insert at position 0 the new augmented start prodution*/
        grammar.productions.insert(grammar.productions.begin(), newProduction);
#if defined(DEBUG_MACRO)
        grammar.initDebugger();
        printf("============Augmented Grammar==============\n");
        grammar.print();
#endif
    }

    // Create the initial state
    {
        /* These are the states or LR(1) items (Ii)*/
        std::vector<item_t> tempLRItems;
        tempLRItems.reserve(20);

        /* Create the initial state */
        tempLRItems.emplace_back(item_t());
        tempLRItems[0].lookAhead.reserve(1);
        tempLRItems[0].lookAhead.emplace_back("$");
        tempLRItems[0].production = grammar.productions[0];
#ifdef DEBUG_MACRO
        tempLRItems[0].initDebugger();
        printf("=========Compute=initial=closure============\n");
        printf("closure(");
        tempLRItems[0].print();
        printf(")\n");
#endif

        closure(tempLRItems[0]);
    }
}

std::vector<std::vector<std::string>> Clr::constructActionsTable(std::vector<item_t> canonicalCollection)
{

    return actionsTable;
}

std::vector<std::vector<std::string>> Clr::constructGotoTable(std::vector<item_t> canonicalCollection)
{
    return gotoTable;
}
