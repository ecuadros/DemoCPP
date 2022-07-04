
#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

void printSum(long num) 
{
  // create coll with num sequences of 0.1 0.3 0.0001:
  std::vector<double> coll;
  coll.reserve(num * 4);
  for (long i=0; i < num; ++i) {
    coll.insert(coll.end(), {0.1, 0.3, 0.00001});
  }

  auto sum1 = std::accumulate(coll.begin(), coll.end(),
                              0.0);
  std::cout << "accumulate(): " << sum1 << '\n';
  auto sum2 = std::reduce(std::execution::par,
                          coll.begin(), coll.end(),
                          0.0);
  std::cout << "reduce():     " << sum2 << '\n';
  std::cout << (sum1==sum2 ? "equal\n" : "differ\n");
}

#include<iomanip>

int main()
{
  std::cout << std::setprecision(20);
  printSum(1);
  printSum(1000);
  printSum(1000000);
  printSum(10000000);
}

