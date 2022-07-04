
#include <iostream> 
#include <vector>
#include <iterator> 
#include <algorithm>  // for sample()
#include <random>     // for random devices and engines

int main()
{
  // initialize a vector of 10,000 string values:
  std::vector<std::string> coll;
  for (int i=0; i < 10000; ++i) {
    coll.push_back("value" + std::to_string(i));
  }

  // initialize a Mersenne Twister engine with a random seed:
  std::random_device rd;   // random seed (if supported)
  std::mt19937 eng{rd()};  // Mersenne twister engine

  // initialize destination range (must be big enough for 10 elements):
  std::vector<std::string> subset;
  subset.resize(100);

  // copy 10 randomly selected values from the source range to the destination range:
  auto end = std::sample(coll.begin(), coll.end(),
                         subset.begin(),
                         10,
                         eng);

  // print extracted elements (using return value as new end):
  std::for_each(subset.begin(), end,
                [] (const auto& s) {
                  std::cout << "random elem: " << s << '\n';
                });
}

