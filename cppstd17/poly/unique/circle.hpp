
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

  virtual void move(Coord c) override {
    center += c;
  }
  virtual void draw() const override {
    std::cout << "circle '" << name << "' at " << center
              << " with radius " << radius << '\n';
  }

  [[nodiscard]] virtual std::unique_ptr<GeoObj> clone() const override {
    return std::make_unique<Circle>(*this);
  }
};

#endif

