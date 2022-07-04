
#include <iostream>
#include "incomplete.hpp"

int main()
{
  // create NodeIncomplete tree:
  NodeIncomplete root{"top"};
  root.add(NodeIncomplete{"elem1"});
  root.add(NodeIncomplete{"elem2"});
  root[0].add(NodeIncomplete{"elem1.1"});

  // print NodeIncomplete tree:
  root.print();
}

