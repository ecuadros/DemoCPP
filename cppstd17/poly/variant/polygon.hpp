
#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "geoobj.hpp"
#include <iostream>
#include <array>
#include <cassert>

class Polygon : public GeoObj {
 private:
  std::array<Coord,100> points;
  int size;
 public:
  // constructor for name and list of Coord's
  Polygon (std::string n, std::initializer_list<Coord> pl)
   : GeoObj{std::move(n)}, size{static_cast<int>(pl.size())} {
       assert(pl.size() <= points.size());
       int idx{0};
       for (const auto& p : pl) {
         points[idx++] = p;
       }
  }

  void move(Coord c) {
    for (int i=0; i<size; ++i) {
      points[i] += c;
    }
  }
  void draw() const {
    std::cout << "polygon '" << name << "' over";
    for (int i=0; i<size; ++i) {
      std::cout << " " << points[i];
    }
    std::cout << "\n";
  }

  int numPoints() const {
    return size;
  }
};

#endif

