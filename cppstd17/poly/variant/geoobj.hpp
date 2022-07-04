
#ifndef GEOOBJ_HPP
#define GEOOBJ_HPP

#include "coord.hpp"
#include <string>

// abstract base class
class GeoObj
{
 protected:
  std::string name;

  GeoObj(std::string n)  // protected to make class abstract
   : name{std::move(n)} {
  }
 public:
  std::string getName() && {
    return std::move(name);
  }
  const std::string& getName() const& {
    return name;
  }
};

#endif

