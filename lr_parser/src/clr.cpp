#include "clr.h"
#include "state.h"
#include "typedefs.h"
#include "unordered_map"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <string>
#include <vector>

/*==============================================================*/
/*                 Constans and local variables                 */
/*==============================================================*/
static std::unordered_map<State, std::unordered_map<std::string, State>>
    gotoGraph;
static State initialState;
static std::queue<State> nextState;
static std::vector<uint64_t> freq;
static int stateIdx = 0;
static int transistionsCnt = 0;
/*==============================================================*/
/*              Global Parsable Implementation                  */
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

void Clr::constructGotoGraph() {
  std::string symbol;
  uint64_t hash;
  uint8_t idx = 1;
  freq.reserve(20);

  while (!nextState.empty()) {
    State temp;
    freq.emplace_back(nextState.front().id);
    for (auto i : nextState.front().items) {

      /* #if defined(DEBUG_MACRO) */
      /*   i.initDebugger(); */
      /*   printf("goto( "); */
      /*   i.print(); */
      /*   printf(")"); */
      /* #endif */
      if ((i.dotPos != i.production.rhs.size())) {
        temp = State(goto_(i, symbol));
        hash = std::hash<State>()(temp);
        temp.id = hash;
        temp.idx = idx;
        /* printf("%d - %d ",temp.id,nextState.front().id); */
        if (std::find(freq.begin(), freq.end(), temp.id) != freq.end()) {
          /* printf("reference found!\n"); */
          for (auto it : gotoGraph) {
            for (auto j : it.second) {
              if (temp.id == j.second.id) {
                /* printf("%d ",j.second.idx); */
                temp.idx = j.second.idx;
                break;
              }
            }
          }
          gotoGraph[nextState.front()][symbol] = temp;
          /* printf("\n"); */
          continue;
        }
        freq.emplace_back(hash);
        /* printf("%d -> %d\n",nextState.front().idx,temp.idx); */
        gotoGraph[nextState.front()][symbol] = temp;
        nextState.push(temp);
        idx++;
      }
      /* else{ printf("\n");} */
    }
    nextState.pop();
  }

  std::sort(freq.begin(), freq.end());
  auto it = std::unique(freq.begin(), freq.end());
  freq.erase(it, freq.end());
  /* printf("%d\n", freq.size()); */
}

/* Add I by moving dot after X. */
/* Apply closure to first step. */
std::vector<item_t> Clr::goto_(item_t state, std::string &symbol) {
  std::vector<item_t> output;

  symbol = state.production.rhs[state.dotPos];
  state.dotPos++;

  /* #ifdef DEBUG_MACRO */
  /*     printf(" computing closure\n"); */
  /*       for(auto i: output){ */
  /*         i.initDebugger(); */
  /*         i.print('\n'); */
  /*       } */
  /* #endif */
  closure(state, output);
  output.insert(output.begin(), state);

  return output;
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
void Clr::closure(item_t item, std::vector<item_t> &output) {
  item_t tempItem;
  /* item.initDebugger(); */
  /* item.print('\n'); */
  // Find all productions that start with the non-terminal that is after dot
  for (production_t production : grammar.productions) {
    std::vector<std::string> firstArgs;
    firstArgs.reserve(20);

    if (item.production.rhs[item.dotPos] == production.lhs) {
      tempItem.production = production;

      /*compute first*/
      {
        /*prepare the first arguments*/
        for (int i = item.dotPos + 1; i < item.production.rhs.size(); i++) {
          firstArgs.emplace_back(item.production.rhs[i]);
        }
        for (std::string symbol : item.lookAhead) {
          firstArgs.emplace_back(symbol);
        }

        tempItem.lookAhead = first(firstArgs);
        /* #if defined(DEBUG_MACRO) */
        /*             tempItem.initDebugger(); */
        /*             tempItem.print('\n'); */
        /* #endif */
      }
      output.emplace_back(tempItem);
      closure(tempItem, output);
    }
  }
}

/**
 * @note We do not include $ in a set, it is the "null terminal"
 * Rules to Compute FIRST Set
 * If x is a terminal, then FIRST(x) = { ‘x’ }
 * If x-> ?, is a production rule, then add ? to FIRST(x).
 * If X->Y1 Y2 Y3….Yn is a production,
 * FIRST(X) = FIRST(Y1)
 * If FIRST(Y1) contains? then FIRST(X) = { FIRST(Y1) – ? } U { FIRST(Y2) }
 * If FIRST (Yi) contains ? for all i = 1 to n, then add ? to FIRST(X).
 */
std::vector<std::string> Clr::first(std::vector<std::string> symbols) {

  std::vector<std::string> temp;
  temp.reserve(20);

  if (symbols[0] == "$")
    return symbols;
  for (std::string symbol : symbols) {
    if (symbol == "$")
      continue;

    // the symbol is a non-terminal
    if (std::find(grammar.nonTerminals.begin(), grammar.nonTerminals.end(),
                  symbol) != grammar.nonTerminals.end()) {
      std::vector<std::string> firstArgs;
      firstArgs.reserve(20);

      /*prepare the first arguments*/
      for (production_t production : grammar.productions) {
        if (production.lhs == symbol) {
          std::vector<std::string> functionBuffer;
          functionBuffer.push_back(production.rhs[0]);

          for (auto str : first(functionBuffer))
            temp.emplace_back(str);
        }
      }
    } else
    /*the symbol is a terminal*/
    {
      temp.emplace_back(symbol);
    }
  }
  return temp;
}

std::vector<std::string> Clr::follow(std::vector<std::string> symbols) {
  std::vector<std::string> temp;
  return temp;
}

/*==============================================================*/
/*                Global CLR Implementation                     */
/*==============================================================*/

void Clr::setGrammar(grammar_t grammar) { this->grammar = grammar; }

void Clr::constructDFA() {
  /*
      Note:
          - By design the dot is already added for each LR(1) item, see item_t
     struct.
          - That will result in one less step for the initial I0 state.
  */
  State state;
  state.items.reserve(20);

  // Augment the grammar
  {
    std::vector<std::string> temp;
    temp.reserve(1);
    temp.emplace_back(grammar.productions[0].lhs);

    production_t newProduction = {/*Lhs*/ grammar.productions[0].lhs + "'",
                                  /*Rhs*/ temp};
    /* #if defined(DEBUG_MACRO) */
    /*         newProduction.initDebugger(); */
    /* #endif */

    /*Insert at position 0 the new augmented start prodution*/
    grammar.productions.insert(grammar.productions.begin(), newProduction);
    /* #if defined(DEBUG_MACRO) */
    /*         grammar.initDebugger(); */
    /*         printf("============Augmented Grammar==============\n"); */
    /*         grammar.print(); */
    /* #endif */
  }

  // Create the initial state
  {
    /* Create the initial state */
    initialState.items.emplace_back();
    initialState.items[0].lookAhead.reserve(1);
    initialState.items[0].lookAhead.emplace_back("$");
    initialState.items[0].production = grammar.productions[0];
    /* #ifdef DEBUG_MACRO */
    /*         initialState.items[0].initDebugger(); */
    /*         printf("=========Compute=initial=closure============\n"); */
    /*         printf("closure("); */
    /*         initialState.items[0].print(); */
    /*         printf("): \n"); */
    /* #endif */

    closure(initialState.items[0], initialState.items);
    // initialState.items[0].initDebugger();

    /* for(auto i:initialState.items){ */
    /*       i.initDebugger(); */
    /*       i.print('\n'); */
    /* } */
  }

  {
    /* printf("=========Compute=goto=graph============\n"); */
    initialState.id = std::hash<State>()(initialState);
    nextState.push(initialState);
    gotoGraph[initialState]["root"] = initialState;
    constructGotoGraph();
    /* printf("========Print=goto=graph============\n"); */
    /* for(auto i: gotoGraph){ */
    /*   for(auto j: i.second){ */
    /*     printf("\n======%s========\n",j.first.data()); */
    /*     for(auto item : j.second.items){ */
    /*         item.initDebugger(); */
    /*         item.print('\n'); */
    /*     } */
    /*   } */
    /* } */
  }
}

void Clr::constructActionsTable() {
  std::string output[20][20];
  std::string heading[20];
  // INIT
  {
    for (auto symbol : grammar.terminals) {
      for (int i = 0; i < freq.size(); i++) {
        actionsTable[symbol][i] = "0";
      }
    }

    for (int i = 0; i < freq.size(); i++) {
      actionsTable["$"][i] = "0";
    }
    actionsTable["$"][1] = "accept";

    /* for (auto i : actionsTable) { */
    /*   printf("%s ", i.first.data()); */
    /* } */
  }

  /* printf("\n"); */

  /* for(auto i: actionsTable){ */
  /*   printf("%s\n\n",i.first.data()); */
  /*   for(auto j: i.second){ */
  /*     printf("%s\n",j.second.data()); */
  /*   } */
  /*   /1* printf("\n"); *1/ */
  /* } */
  for (auto i : gotoGraph) {
    /* printf("%d parent\n",i.first.idx); */
    /* for(auto it: i.first.items){ */
    /*   it.initDebugger(); */
    /*   it.print('\n'); */
    /* } */
    for (auto j : i.second) {
      /* printf("%d\n",j.second.idx); */
      /* printf("\n======%s========\n", j.first.data()); */
      if (std::find(grammar.nonTerminals.begin(), grammar.nonTerminals.end(),
                    j.first) == grammar.nonTerminals.end()) {
        /* printf("%d %d\n", j.second.items[0].dotPos, */
               /* j.second.items[0].production.rhs.size()); */
        /* printf("%d->%d\n", i.first.idx, j.second.idx); */
        // reduce
        if ((j.second.items[0].dotPos ==
             j.second.items[0].production.rhs.size())) {

          /* printf("%d\n",j.second.idx); */
          for (int i = 0; i < grammar.productions.size(); i++) {
            if (grammar.productions[i] == j.second.items[0].production) {
              for (auto str : j.second.items[0].lookAhead) {
                actionsTable[str][j.second.idx] = "r" + std::to_string(i);
              }
              /* printf("%d\n",i); */
            }
          }
          /* printf("%s:%d=%s\n", j.first.data(), i.first.idx, */
          /*        ("d" + std::to_string(j.second.idx)).data()); */
          actionsTable[j.first][i.first.idx] =
              "d" + std::to_string(j.second.idx);
          /* printf("leaf\n"); */
        } else {
          // shift
          /* printf("%s:%d=%s\n", j.first.data(), i.first.idx, */
          /*        ("d" + std::to_string(j.second.idx)).data()); */
          actionsTable[j.first][i.first.idx] =
              "d" + std::to_string(j.second.idx);
        }
      } else {

        /* printf("%d->%d\n", i.first.idx, j.second.idx); */
        // reduce
        if (j.second.items[0].dotPos ==
            j.second.items[0].production.rhs.size()) {

          /* printf("%d->%d\n", i.first.idx, j.second.idx); */
          /* printf("%d\n",j.second.idx); */
          for (int i = 0; i < grammar.productions.size(); i++) {
            if (grammar.productions[i] == j.second.items[0].production) {
              for (auto str : j.second.items[0].lookAhead) {
                actionsTable[str][j.second.idx] = "r" + std::to_string(i);
              }
              /* printf("%d\n",i); */
            }
          }
          /* printf("leaf\n"); */
        }
      }

      /* for (auto item : j.second.items) { */
      /*   item.initDebugger(); */
      /*   item.print('\n'); */
      /* } */
    }
  }
  actionsTable["$"][1] = "accept";

  // convert to readable form
  {
    int it0=-1;
    for (auto i : actionsTable) {
      if(it0!=-1)
        heading[it0]=i.first;
      int it1=0;
      for (auto j : i.second) {
        output[it0][it1] = j.second;
        it1++;
      }
      it0++;
      /* printf("\n"); */
    }
    for(int i=0;i<actionsTable.size();i++){
      std::reverse(output[i],output[i]+freq.size());
    }
  }

  /* printf("===========Actions Table============\n"); */
  /* for (int i=0;i<actionsTable.size()-1;i++) { */
  /*     printf("%s: ",heading[i].data()); */
  /*     for (int j=0;j<freq.size();j++) { */
  /*       printf("%s ",output[i][j].data()); */
  /*     } */
  /*     printf("\n"); */
  /* } */

  printf("===========Actions Table============\n");
  for (int i=0;i<freq.size();i++) {
      /* printf("%s: ",heading[i].data()); */
      if(i==0){
        for (int j=actionsTable.size()-2;j>=0;j--) {
          printf("|%s\t",heading[j].data());
        }
        printf("|\n-------------------------\n");
      }
      for (int j=actionsTable.size()-2;j>=0;j--) {
        printf("|%s\t",output[j][i].data());
        if(j==0)printf("|\n");
      }
      /* printf(" "); */
  }
}


void Clr::constructGotoTable() {
  int output[20][20];
  std::string heading[20];

  // INIT
  {
    for (auto symbol : grammar.nonTerminals) {
      for (int i = 0; i < freq.size(); i++) {
        gotoTable[symbol][i] = 0;
      }
    }
    int j = 0;
    for (auto i : gotoTable) {
      /* printf("%s ", i.first.data()); */
      heading[j++] = i.first;
    }
  }

  printf("\n");
  for (auto i : gotoGraph) {
    for (auto j : i.second) {
      /* printf("\n======%s========\n", j.first.data()); */
      if (std::find(grammar.terminals.begin(), grammar.terminals.end(),
                    j.first) == grammar.terminals.end()) {
        /* printf("%s:%d=%s\n",j.first.data(),i.first.idx,("d"+std::to_string(j.second.idx)).data());
         */
        /* printf("%d->%d\n", i.first.idx, j.second.idx); */
        gotoTable[j.first][i.first.idx] = j.second.idx;
      }

      /* for (auto item : j.second.items) { */
      /*   item.initDebugger(); */
      /*   item.print('\n'); */
      /* } */
    }
  }

  // convert to readable form
  {
    int it0 = -1;
    int it1 = 0;

    for (auto i : gotoTable) {
      /* printf("%s\n\n",i.first.data()); */
      it1 = 0;
      for (auto j : i.second) {
        output[it0][it1] = j.second;
        /* printf("output[%d][%d]= %d\n",it1,it0,output[it1][it0]); */
        it1++;
      }
      it0++;
    }
      for(int i=0;i<gotoTable.size()-1;i++){
      std::reverse(output[i], output[i] + freq.size());
    }
  }

  /* printf("==========Goto table========\n"); */
  /* for (int i = 0; i < gotoTable.size() - 1; i++) { */
  /*   printf("%s: ", heading[i].data()); */
  /*   for (int j = 0; j < freq.size(); j++) { */
  /*     printf("%d ", output[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  printf("===========Actions Table============\n");
  for (int i=0;i<freq.size();i++) {
      if(i==0){
        for (int j=gotoTable.size()-2;j>=0;j--) {
          printf("|%s\t",heading[j].data());
        }
        printf("|\n-------------------------\n");
      }
      for (int j=gotoTable.size()-2;j>=0;j--) {
        printf("|%d\t",output[j][i]);
        if(j==0)printf("|\n");
      }
      /* printf(" "); */
  }

}
