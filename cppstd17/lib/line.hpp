
#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>
#include "coord.hpp"

class Line
{
  private:
    Coord from;
    Coord to;
  public:
    Line (Coord f, Coord t)
     : from{f}, to{t} {  }

    void move(const Coord& c)
    { from += c;
      to   += c;
    }

    void draw() const
    {   std::cout << "line from " << from << " to " << to << '\n';
    }
};

#endif

