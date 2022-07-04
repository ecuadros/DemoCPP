
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <execution>  // for the execution policy
#include <cmath>      // for sqrt()
#include "timer.hpp"

int main()
{
  int numElems = 1000;
  struct Data
  { double value;  // initial value
    double sqrt;   // parallel computed square root
  };

  // initialize numElems values without square root:
  std::vector<Data> coll;
  coll.reserve(numElems);
  for (int i=0; i<numElems; ++i)
      coll.push_back(Data{i * 4.37, 0});

  // parallel computation of square roots:
  for_each(std::execution::par,
           coll.begin(), coll.end(),
           [](auto& val)
           {
             val.sqrt = std::sqrt(val.value);
           });
}

