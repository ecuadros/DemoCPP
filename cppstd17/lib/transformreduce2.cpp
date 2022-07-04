
#include <array>
#include <iostream>
#include <numeric>
#include <string>

int main()
{
  std::array coll1{3, 1, 7, 5, 4, 1, 6, 3};
  std::array coll2{1, 2, 3, 4, 5, 6, 7, 8};

  // process sum of squared values:
  std::cout << "sum of squared:         "
       << std::transform_reduce(coll1.cbegin(), coll1.cend(),  // 1st range
                                coll1.cbegin(),                // 2nd range
                                0L) 
       << '\n';

  // process product of differences of corresponding arguments:
  std::cout << "product of differences: "
       << std::transform_reduce(coll1.cbegin(), coll1.cend(),  // 1st range
                                coll2.cbegin(),                // 2nd range
                                1L,
                                std::multiplies{}, std::minus{})
       << '\n';

  // process sum (concatenation) of concatenated digits:
  std::cout << "sum of combined digits: "
       << std::transform_reduce(coll1.cbegin(), coll1.cend(),  // 1st range
                                coll2.cbegin(),                // 2nd range
                                std::string{},
                                std::plus{},
                                [] (auto x, auto y) {
                                  return std::to_string(x) +
                                         std::to_string(y) + " ";
                                })
       << '\n';
}

