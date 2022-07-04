
#ifndef GEOOBJ_HPP
#define GEOOBJ_HPP

#include "coord.hpp"
#include <string>
#include <memory>

// abstract base class
class GeoObj
{
 protected:
  std::string name;                 // name of the geometric object
  GeoObj(const GeoObj&) = default;  // disable slicing
  GeoObj(GeoObj&&) = default;       // disable slicing
 public:
  GeoObj(std::string n = {})
   : name{n} {
  }

  virtual std::string getName() && final {
    return std::move(name);
  }
  virtual const std::string& getName() const& final {
    return name;
  }

  virtual void move(Coord) = 0;
  virtual void draw() const = 0;

  virtual ~GeoObj() = default;
  GeoObj& operator= (const GeoObj&) = delete;  // disable slicing
  GeoObj& operator= (GeoObj&&) = delete;       // disable slicing

  [[nodiscard]] virtual std::unique_ptr<GeoObj> clone() const = 0;
};

#endif

