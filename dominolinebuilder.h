#ifndef DOMINOLINEBUILDER_H
#define DOMINOLINEBUILDER_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>
#include <list>

struct Domino
{
   std::string blueSymbol;
   std::string redSymbol;
   std::string Symbol;
   Domino* previous = nullptr;
   Domino* next = nullptr;

   Domino(std::string theBlueSymbol, std::string theRedSymbol);
};

class DominoLineBuilder
{
  public:
    DominoLineBuilder(unsigned long int totalNumberOfDominoes, std::istream& dominoInputData);
    bool UpdatednextRight();
    bool nextRight();
    bool nextLeft();
    bool oneDominoSymbol();
    void displayLine(std::ostream& theOutputStream) const;

    ~DominoLineBuilder();

  private:
    Domino* lastDisorderedDomino = nullptr;
    std::vector<Domino> orderedLine;
    std::unordered_map<std::string, Domino*> symbolMap;

};

#endif
