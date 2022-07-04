
#include <iostream>
#include <vector>
#include <numeric>   // for reduce()
#include <execution>

void printSum(long num) 
{
  // create coll with num sequences of 1 2 3 4:
  std::vector<long> coll;
  coll.reserve(num * 4);
  for (long i=0; i < num; ++i) {
    coll.insert(coll.end(), {1, 2, 3, 4});
  }

  auto sum = std::reduce(std::execution::par,
                         coll.begin(), coll.end(),
                         0L);
  std::cout << "reduce():     " << sum << '\n';
}

int main()
{
  printSum(1);
  printSum(1000);
  printSum(1000000);
  printSum(10000000);
}

