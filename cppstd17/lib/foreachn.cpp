
#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm>  // for for_each_n()

int main()
{
  // initialize a vector of 10,000 string values:
  std::vector<std::string> coll;
  for (int i=0; i < 10000; ++i) {
    coll.push_back(std::to_string(i));
  }

  // modify first 5 elements:
  for_each_n(coll.begin(), 5,
             [] (auto& elem) {
               elem = "value" + elem;
             });

  // print first 10 elements:
  for_each_n(coll.begin(), 10,
             [] (const auto& elem) {
               std::cout << elem << '\n';
             });
}

