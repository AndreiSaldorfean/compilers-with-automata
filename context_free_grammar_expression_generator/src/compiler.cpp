#include "compiler.h"
#include "file.h"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
#include <stdio.h>
#include <string.h>

static int tokenize(const char *str, std::string *tokens) {
  int prevSize = 0;
  int noTokens = 0;

  for (int i = 0; str[i]; i++) {
    tokens[i] = '\0';
    if (str[i] == '|') {
      *tokens = str + prevSize;
      (*tokens).resize(i - prevSize);
      prevSize = i + 1;
      tokens++;
      noTokens++;
    }
  }
  *tokens = str + prevSize;
  return noTokens;
}

static uint8_t s_get_size(const std::string *str) {
  uint8_t size;
  for (size = 0; str[size][0]; size++)
    ;
  return size;
}

Complier::Complier() {
  memset(terminals, 0, sizeof(terminals));
  memset(nonTerminals, 0, sizeof(nonTerminals));
}

/* I know this could be implemented more elegantly with try-catch but I am
 * lazy*/
bool Complier::parse_grammer(const char *fileName) {
  int length = 0;
  char line[BUFFER_SIZE];
  std::string tokens[MAX_PRODUCTIONS_TOKENS];
  File<std::ifstream> fileHandler(fileName);
  memset(line, 0, sizeof(line));

  // Read start symbol
  if (!fileHandler.readline(&startSymbol))
    return false;

  // Read non-terminals
  if (!fileHandler.readline(terminals))
    return false;

  // Read terminals
  if (!fileHandler.readline(nonTerminals))
    return false;

  // Read grammer productions
  if (!fileHandler.readline(line))
    return false;
  for (int lineIndex = 0; (line[0] != '\n' && line[0] != '\0'); lineIndex++) {
    int bufferSize = tokenize(line, tokens) + 1;
    tokens[0].erase(0, 2);

    for (int i = 0; i < bufferSize; i++) {
      productions[line[0]][i] = tokens[i];
    }

    if (!fileHandler.readline(line))
      return false;
  }
  return true;
}

void Complier::print_grammer() {
  for (auto i : productions) {
    printf("%c: ", i.first);
    for (int j = 0; !i.second[j].empty(); j++) {
      printf("%s ", i.second[j].c_str());
    }
    printf("\n");
  }
}

/* NOT USED */
void Complier::parse_expression(const char *fileName) {
  File<std::ifstream> fileHandler(fileName);
  char line[BUFFER_SIZE];
  fileHandler.readline(line);
  printf("Expression: %s\n", line);
}

void Complier::generate_random_expression(std::function<int64_t()> rng,
                                          bool printSteps) {
  File<std::ofstream> fileHandler("out/output.txt");
  int randIndex = 0;
  char lineLength = 0;
  char index = 0;
  char expressionQueue[QUEUE_SIZE];
  char cursor = 0;
  memset(expressionQueue, 0, sizeof(expressionQueue));

  /* Insert the start symbol in the expression queue */
  lineLength = s_get_size(productions[startSymbol]);
  randIndex = rng() % lineLength;
  strcpy_s(expressionQueue, productions[startSymbol][randIndex].c_str());
  if (printSteps)
    fileHandler.write("Start symbol (%d): %s\n", randIndex, expressionQueue);

  /* Place the cursor using extream left method*/
  cursor = expressionQueue[index];
  for (int i = 0; i < GRAMMAR_LIMIT; i++) {
    char buffer[BUFFER_SIZE];

    /* Check if the char under the cursor is a terminal */
    if (productions[cursor][randIndex].empty()) {

      /* Go to the nearest non-terminal*/
      while (std::find(nonTerminals, nonTerminals + MAX_GRAMMER_LENGTH,
                       cursor) >= nonTerminals + sizeof(nonTerminals)) {
        index++;
        cursor = expressionQueue[index];

        /* If the expression queue is empty then step out*/
        if (cursor == '\0') {
          // fileHandler.write("\n");
          if (0 == printSteps)
            return;
          fileHandler.write("%d.(%d): %s", i + 1, randIndex, expressionQueue);
        }
      }
    }

    /* Pick a random production from the selected terminal */
    lineLength = s_get_size(productions[cursor]);
    randIndex = rand() % lineLength;

    // Use extream left method
    strcpy_s(buffer, expressionQueue + index + 1);
    memcpy(expressionQueue + index, productions[cursor][randIndex].c_str(),
           productions[cursor][randIndex].size());
    memcpy(expressionQueue + index + productions[cursor][randIndex].size(),
           buffer, sizeof(buffer));

    if (printSteps)
      fileHandler.write("%d.(%d): %s\n", i + 1, randIndex, expressionQueue);
    cursor = expressionQueue[index];
  }
  fileHandler.write("%s\n", expressionQueue);
  // fileHandler.write("\n");
}
