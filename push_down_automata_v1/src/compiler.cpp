#include "compiler.h"
#include "file.h"
#include "typedefs.h"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <string.h>

static int tokenize(const char *str, std::string *tokens,
                    const char delimiter = '|')
{
  std::string buffer = str;
  int index = 0;

  for (int i = buffer.find_first_not_of(delimiter); i != -1;
       i = buffer.find_first_not_of(delimiter, i))
  {
    tokens[index] = buffer.substr(i, buffer.find(delimiter, i) - i);
    i += tokens[index++].size() + 1;
  }
  return index;
}

static uint8_t sGetSize(const std::string *str)
{
  int size;
  for (size = 0; !str[size].empty(); size++)
    ;
  return size;
}

static void sCopy(std::string source[], std::string destination[], int length)
{
  for (int i = 0; i < length; i++)
  {
    destination[i] = source[i];
  }
}

static void clear(std::string arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    arr[i].clear();
  }
}

static void strip(char *line /* out */, const char delimiter = ' ')
{
  std::string buffer = line;
  memset(line, 0, sizeof(line));

  buffer.erase(std::remove(buffer.begin(), buffer.end(), delimiter),
               buffer.end());
  memcpy(line, buffer.c_str(), buffer.size());
}

static int findPerfectMatch(std::string container[], std::string str, int container_size)
{
  for (int i = 0; i < container_size; i++)
  {
    if (container[i] == str)
      return i;
  }
  return -1;
}


static void tokenizeFromArray(std::string destination[], std::string references[], char source[])
{
  int size = sGetSize(references);
  int idx = -1;
  int j = 0;
  std::string buffer = "";
  for (int i = 0; i < source[i];)
  {
    if (idx == -1)
    {
      buffer.push_back(source[i]);
      i++;
    }
    idx = findPerfectMatch(references, buffer, size);
    if (idx != -1)
    {
      destination[j++] = references[idx];
      buffer = "";
    }
  }
}

static int identifyNumOfItems(std::string token,std::string nonTerm[],std::string term[]){
  int nonTermSize = sGetSize(nonTerm);
  int termSize = sGetSize(term);
  int size = 0;
  int idx = -1;
  int j = 0;
  std::string buffer = "";
  std::string arrBuffer[BUFFER_SIZE];

  {
    for(int i=0;i<nonTermSize;i++){
      arrBuffer[j++] = nonTerm[i];
    }
    for(int i=0;i<termSize;i++){
      arrBuffer[j++] = term[i];
    }
  }

  for (int i = 0; i < token[i];)
  {
    if (idx == -1)
    {
      buffer.push_back(token[i]);
      i++;
    }
    idx = findPerfectMatch(arrBuffer, buffer, j);
    if (idx != -1)
    {
      size++;
      buffer = "";
    }
  }

  return size;
}

Compiler::Compiler() : Pda()
{
  memset(terminals, 0, sizeof(terminals));
  memset(nonTerminals, 0, sizeof(nonTerminals));
}

bool Compiler::parseGrammer(const char *fileName)
{
  int length = 0;
  int pdaIndex = 0;
  char line[BUFFER_SIZE];
  std::string tokens[MAX_GRAMMER_LENGTH];
  File<std::ifstream> fileHandler(fileName);
  memset(line, 0, sizeof(line));

  // Read start symbol
  {
    if (!fileHandler.readline(line))
      return false;
    startSymbol = line;
  }

  // Read non-terminals
  {
    if (!fileHandler.readline(line))
      return false;
    length = tokenize(line, tokens, ' ');
    sCopy(tokens, nonTerminals, length);
  }

  // Read terminals
  {
    clear(tokens, length);
    if (!fileHandler.readline(line))
      return false;
    length = tokenize(line, tokens, ' ');
    sCopy(tokens, terminals, length);
  }

  // Read grammer productions
  if (!fileHandler.readline(line))
    return false;
  for (int lineIndex = 0; (line[0] != '\n' && line[0] != '\0'); lineIndex++)
  {
    clear(tokens, length);
    length = tokenize(line, tokens, ' ');
    for (int i = 0; i < length - 1; i++)
    {
      productions[tokens[0]][i] = tokens[i + 1];
      pdaProductions[pdaIndex] = tokens[0];
      pdaProductionSize[pdaIndex++] = 2* identifyNumOfItems(tokens[i+1],nonTerminals,terminals);
    }

    if (!fileHandler.readline(line))
      return false;
  }
  return true;
}

bool Compiler::parseActions(const char *fileName)
{
  File<std::ifstream> fileHandler(fileName);
  std::string tokens[MAX_PRODUCTIONS_TOKENS];
  std::string heading[BUFFER_SIZE];
  char line[BUFFER_SIZE];
  int idx = 0;
  memset(line, 0, sizeof(line));

  // Read table heading
  fileHandler.readline(line);
  tokenize(line, heading, ' ');

  for (; fileHandler.readline(line);)
  {
    clear(tokens, MAX_PRODUCTIONS_TOKENS);

    int size = tokenize(line, tokens, ' ');
    for (uint8_t i = 0; i < size; i++)
    {
      actions[idx][heading[i]] = tokens[i];
    }
    idx++;
  }

  return true;
}

bool Compiler::parseJump(const char *fileName)
{
  File<std::ifstream> fileHandler(fileName);
  std::string heading[BUFFER_SIZE];
  std::string tokens[MAX_PRODUCTIONS_TOKENS];
  char line[BUFFER_SIZE];
  int idx = 0;
  memset(line, 0, sizeof(line));

  // Read table heading
  fileHandler.readline(line);
  tokenize(line, heading, ' ');

  for (; fileHandler.readline(line);)
  {
    int size = tokenize(line, tokens, ' ');
    for (uint8_t i = 0; i < size; i++)
    {
      jump[idx][heading[i]] = tokens[i];
    }
    idx++;
  }

  return true;
}

void Compiler::printGrammer()
{
  for (auto i : productions)
  {
    printf("%s: ", i.first.c_str());
    for (int j = 0; !i.second[j].empty(); j++)
    {
      printf("%s ", i.second[j].c_str());
    }
    printf("\n");
  }
}

/* NOT USED YET*/
void Compiler::parseExpression(const char *fileName)
{
  File<std::ifstream> fileHandler(fileName);
  char line[BUFFER_SIZE];
  fileHandler.readline(line);
  printf("Expression: %s\n", line);
}

void Compiler::generateRandomExpression()
{
  File<std::ofstream> fileHandler("out/output.txt");
  int randIndex = 0;
  char lineLength = 0;
  char index = 0;
  char expressionQueue[QUEUE_SIZE];
  std::string cursor = 0;
  memset(expressionQueue, 0, sizeof(expressionQueue));

  /* Initialize the random number generator*/
  std::srand(std::time(0));

  /* Insert the start symbol in the expression queue */
  lineLength = sGetSize(productions[startSymbol]);
  randIndex = rand() % lineLength;
  strcpy_s(expressionQueue, productions[startSymbol][randIndex].c_str());
  fileHandler.write("Start symbol (%d): %s\n", randIndex, expressionQueue);

  /* Place the cursor using extream left method*/
  cursor = expressionQueue[index];
  for (int i = 0; i < 64; i++)
  {
    char buffer[BUFFER_SIZE];

    /* Check if the char under the cursor is a terminal */
    if (productions[cursor][randIndex].empty())
    {

      /* Go to the nearest non-terminal*/
      while (std::find(nonTerminals, nonTerminals + MAX_GRAMMER_LENGTH,
                       cursor) >= nonTerminals + sizeof(nonTerminals))
      {
        index++;
        cursor = expressionQueue[index];

        /* If the expression queue is empty then step out*/
        if (cursor == "\0")
        {
          fileHandler.write("\n");
          return;
        }
      }
    }

    /* Pick a random production from the selected terminal */
    lineLength = sGetSize(productions[cursor]);
    randIndex = rand() % lineLength;

    // Use extream left method
    strcpy_s(buffer, expressionQueue + index + 1);
    memcpy(expressionQueue + index, productions[cursor][randIndex].c_str(),
           productions[cursor][randIndex].size());
    strcpy(expressionQueue + index + productions[cursor][randIndex].size(),
           buffer);

    fileHandler.write("%d.(%d): %s\n", i + 1, randIndex, expressionQueue);
    cursor = expressionQueue[index];
  }
  fileHandler.write("\n");
}

bool Compiler::analyzeLine(inputBand_t *inputBand)
{
  std::string tokens[BUFFER_SIZE];
  std::string ceva = inputBand;
  tokenizeFromArray(tokens, nonTerminals, inputBand);
  int size = sGetSize(tokens);
  tokens[size] = "$";

  return pdaAnalyze(tokens);
}