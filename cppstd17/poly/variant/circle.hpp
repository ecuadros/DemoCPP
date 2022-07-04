
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "geoobj.hpp"
#include <iostream>

class Circle : public GeoObj {
 private:
  Coord center;
  int radius;
 public:
  Circle (std::string n, Coord c, int r)
   : GeoObj{std::move(n)}, center{c}, radius{r} {
  }

  void move(Coord c) {
    center += c;
  }
  void draw() const {
    std::cout << "circle '" << name << "' at " << center
              << " with radius " << radius << '\n';
  }
};

#endif

