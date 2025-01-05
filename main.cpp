#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

#include "dominolinebuilder.h"

using std::chrono::steady_clock;
using std::chrono::nanoseconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::duration_cast;

using namespace std;
using namespace std::chrono;

int main()
{
   const unsigned long int datasetSize = 10;
   const std::string filepath = "C:/Users/Joe Blackbourn/source/repos/dominoes/dominoes-test_data/10/10-input.txt";

   std::ifstream theInputStream(filepath);
   if (!theInputStream.good()) throw std::invalid_argument("Cannot read from specified file.");

   DominoLineBuilder theDominoLine(datasetSize, theInputStream);

   while (theDominoLine.nextRight());

   theDominoLine.displayLine(std::cout);
}
