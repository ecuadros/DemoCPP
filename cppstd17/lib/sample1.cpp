
#include <iostream> 
#include <vector>
#include <string>
#include <iterator> 
#include <algorithm>  // for sample()
#include <random>     // for default_random_engine

int main()
{
  // initialize a vector of 10,000 string values:
  std::vector<std::string> coll;
  for (int i=0; i < 10000; ++i) {
    coll.push_back("value" + std::to_string(i));
  }

  // print 10 randomly selected values of this collection: 
  std::sample(coll.begin(), coll.end(),
              std::ostream_iterator<std::string>{std::cout, "\n"},
              10,
              std::default_random_engine{});
}

