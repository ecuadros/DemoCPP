
#ifndef LAST5_HPP
#define LAST5_HPP

#include <iterator>
#include <iostream>

template<typename T>
void printLast5(const T& coll)
{
  // compute size:
  auto size{std::size(coll)};
  // advance to the position starting at the last 5 elements
  std::cout << size << " elems: ";
  auto pos{std::begin(coll)};
  if (size > 5) {
    std::advance(pos, size - 5);
    std::cout << "... ";
  }
  // print remaining elements:
  for ( ; pos != std::end(coll); ++pos) {
    std::cout << *pos << ' ';
  }
  std::cout << '\n';
}

#endif // LAST5_HPP


