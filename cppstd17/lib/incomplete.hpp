
#ifndef NODE_INCOMPLETE_HPP
#define NODE_INCOMPLETE_HPP

#include <vector>
#include <iostream>
#include <string>

class NodeIncomplete
{
  private:
    std::string value;
    std::vector<NodeIncomplete> children;  // OK since C++17 (NodeIncomplete is an incomplete type here)
  public:
    // create NodeIncomplete with value:
    NodeIncomplete(std::string s) : value{std::move(s)}, children{} {};

    // add child node:
    void add(NodeIncomplete n)
    {  children.push_back(std::move(n));
    }

    // access child node:
    NodeIncomplete& operator[](std::size_t idx)
    {  return children.at(idx);
    }

    // print node tree recursively:
    void print(int indent = 0) const
    { std::cout << std::string(indent, ' ') << value << '\n';
      for (const auto& n : children)
      {    n.print(indent+2);   }
    }
    //...
};

#endif // NODE_INCOMPLETE_HPP

