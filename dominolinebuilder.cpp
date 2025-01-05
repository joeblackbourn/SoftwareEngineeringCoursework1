#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "dominoes/dominolinebuilder.h"

using namespace std;
using namespace std::chrono;
using std::chrono::steady_clock;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;


Domino::Domino(std::string theBlueSymbol, std::string theRedSymbol)
{
   blueSymbol = theBlueSymbol;
   redSymbol = theRedSymbol;
}


DominoLineBuilder::DominoLineBuilder(unsigned long int totalNumberOfDominoes, std::istream& dominoInputData)
{
   auto start = std::chrono::high_resolution_clock::now();

   for (unsigned long int i = 0; i < totalNumberOfDominoes; ++i)
   {
       std::string aBlueSymbol, aRedSymbol, aSymbol;
       std::getline(dominoInputData, aBlueSymbol, ':');
       std::getline(dominoInputData, aRedSymbol, '\n');

       Domino* newDomino = new Domino(aBlueSymbol,aRedSymbol);
       newDomino->previous = lastDisorderedDomino;
       lastDisorderedDomino = newDomino;

       symbolMap[aBlueSymbol] = newDomino;
       symbolMap[aRedSymbol] = newDomino;
       symbolMap[aSymbol] = newDomino;
   }

   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<microseconds>(stop - start);
   std::cout << "Time taken by the DominoLineBuilder function: " << duration.count() << " microseconds" << std::endl;
}

bool DominoLineBuilder::nextRight()
{
    auto start = std::chrono::high_resolution_clock::now();

    if (orderedLine.empty())
    {
        Domino* startingDomino = lastDisorderedDomino;
        orderedLine.push_back(*startingDomino);
        lastDisorderedDomino = lastDisorderedDomino->previous;
        delete startingDomino;
        return true;
    }

    for (Domino* currentDomino = lastDisorderedDomino; currentDomino != nullptr; currentDomino = currentDomino->previous)
    {
        if (currentDomino->blueSymbol == orderedLine.back().redSymbol)
        {
            orderedLine.push_back(*currentDomino);
            return true;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by the nextRight function: " << duration.count() << " microseconds" << std::endl;

    return false;
}

bool DominoLineBuilder::UpdatednextRight()
{
    auto start = std::chrono::high_resolution_clock::now();

   if (orderedLine.empty())
   {
      Domino* startingDomino = lastDisorderedDomino;
      orderedLine.push_back(*startingDomino);
      lastDisorderedDomino = lastDisorderedDomino->previous;
      delete startingDomino;
      return true;
   }

   std::unordered_map<std::string, Domino*> symbolMap;

   for (Domino* currentDomino = lastDisorderedDomino; currentDomino != nullptr; currentDomino = currentDomino->previous)
   {
       symbolMap[currentDomino->blueSymbol] = currentDomino;

   }

   const std::string lastRedSymbol = orderedLine.back().redSymbol;
   auto it = symbolMap.find(lastRedSymbol);
   if (it != symbolMap.end()) {
       orderedLine.push_back(*(it->second));
       return true;
   }

   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<microseconds>(stop - start);
   std::cout << "Time taken by the UpdatednextRight function: " << duration.count() << " microseconds" << std::endl;

   return false;
}


bool DominoLineBuilder::nextLeft()
{

    if (orderedLine.empty())
    {
        Domino* startingDomino = lastDisorderedDomino;
        orderedLine.insert(orderedLine.begin(), *startingDomino);
        lastDisorderedDomino = lastDisorderedDomino->previous;
        delete startingDomino;
        return true;
    }

    std::unordered_map<std::string, Domino*> symbolMap;

    for (Domino* currentDomino = lastDisorderedDomino; currentDomino != nullptr; currentDomino = currentDomino->previous)
    {
        symbolMap[currentDomino->redSymbol] = currentDomino;

    }

    const std::string lastBlueSymbol = orderedLine.front().blueSymbol;
    auto it = symbolMap.find(lastBlueSymbol);
    if (it != symbolMap.end()) {
        orderedLine.insert(orderedLine.begin(), (*(it->second)));
        return true;
    }

    return false;
}


bool DominoLineBuilder::oneDominoSymbol()
{
    auto start = std::chrono::high_resolution_clock::now();

    if (orderedLine.empty())
    {
        Domino* startingDomino = lastDisorderedDomino;
        orderedLine.push_back(*startingDomino);
        lastDisorderedDomino = lastDisorderedDomino->previous;
        delete startingDomino;
        return true;
    }

    std::unordered_map<std::string, Domino*> symbolMap;

    for (Domino* currentDomino = lastDisorderedDomino; currentDomino != nullptr; currentDomino = currentDomino->previous)
    {
        symbolMap[currentDomino->Symbol] = currentDomino;

    }

    const std::string lastSymbol = orderedLine.back().Symbol;
    auto it = symbolMap.find(lastSymbol);
    if (it != symbolMap.end()) {
        orderedLine.push_back(*(it->second));
        return true;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by the oneDominoSymbol function " << duration.count() << " microseconds" << std::endl;

    return false;
}


void DominoLineBuilder::displayLine(std::ostream& outputStream) const
{
    auto start = std::chrono::high_resolution_clock::now();

   for (const Domino eachDomino : orderedLine) 
   {
      outputStream << eachDomino.blueSymbol << ':' << eachDomino.redSymbol << ' ';
   }

   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<microseconds>(stop - start);
   std::cout << "Time taken by the displayLine function: " << duration.count() << " microseconds" << std::endl;
}

DominoLineBuilder::~DominoLineBuilder()
{

    Domino* currentDomino = lastDisorderedDomino;
    while (currentDomino != nullptr)
    {
        Domino* dominoToDelete = currentDomino;
        currentDomino = currentDomino->previous;
        delete dominoToDelete;
    }
    
}