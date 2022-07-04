
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <execution>  // for the execution policy
#include <cstdlib>    // for atoi()
#include "timer.hpp"

int main(int argc, char* argv[])
{
  // initialize numElems from command line (default: 1000)
  int numElems = 1000;
  if (argc > 1) {
    numElems = std::atoi(argv[1]);
  }

  struct Data {
    double value;  // initial value
    double sqrt;   // parallel computed square root
  };

  // initialize numElems values without square root:
  std::vector<Data> coll;
  coll.reserve(numElems);
  for (int i=0; i<numElems; ++i) {
    coll.push_back(Data{i * 4.37, 0});
  }

  // loop to make measurements mature:
  for (int i{0}; i < 5; ++i) {
    Timer t;
    // sequential execution:
    for_each(std::execution::seq,
             coll.begin(), coll.end(),
             [](auto& val) {
               val.sqrt = std::sqrt(val.value);
             });
    t.printDiff("sequential: ");

    // parallel execution:
    for_each(std::execution::par,
             coll.begin(), coll.end(),
             [](auto& val) {
               val.sqrt = std::sqrt(val.value);
             });
    t.printDiff("parallel:   ");
    std::cout << '\n';
  }
}

