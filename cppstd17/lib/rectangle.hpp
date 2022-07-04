
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "coord.hpp"
#include <iostream>

class Rectangle {
  private:
    Coord from;
    Coord to;
  public:
    Rectangle (Coord f, Coord t) : from{f}, to{t} {}

    void move(const Coord& c)
    {
      from += c;
      to += c;
    }

    void draw() const
    {
      std::cout << "rectangle from " << from  << " to " << to << '\n';
    }
};

#endif

