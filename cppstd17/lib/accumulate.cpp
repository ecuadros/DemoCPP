
#include <iostream>
#include <vector>
#include <numeric>   // for accumulate()

void printSum(long num) 
{
  // create coll with num sequences of 1 2 3 4:
  std::vector<long> coll;
  coll.reserve(num * 4);
  for (long i=0; i < num; ++i)
      coll.insert(coll.end(), {1, 2, 3, 4});

  auto sum = std::accumulate(coll.begin(), coll.end(), 0L);
  std::cout << "accumulate(): " << sum << '\n';
  std::cout.flush();
}

int main()
{
  printSum(1);
  printSum(1000);
  printSum(1000000);
  printSum(10000000);
  printSum(1000000000);
}

