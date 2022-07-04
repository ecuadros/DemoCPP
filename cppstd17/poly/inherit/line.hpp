
#ifndef LINE_HPP
#define LINE_HPP

#include "geoobj.hpp"
#include <iostream>

class Line : public GeoObj {
 private:
  Coord from;
  Coord to;
 public:
  Line (std::string n, Coord f, Coord t)
   : GeoObj{std::move(n)}, from{f}, to{t} {
  }

  virtual void move(Coord c) override {
    from += c;
    to += c;
  }
  virtual void draw() const override {
    std::cout << "line '" << name << "' from " << from
              << " to " << to << '\n';
  }

  [[nodiscard]] virtual Line* clone() const override {
    return new Line{*this};
  }
};

#endif

