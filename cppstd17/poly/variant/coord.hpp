
#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>

class Coord {
 private:
  int x{0};     // x coordinate
  int y{0};     // y coordinate
 public:
  // default constructor:
  Coord() = default;
  // other constructor:
  Coord(int xarg, int yarg)
   : x{xarg}, y{yarg} {
  }

  friend Coord operator+ (Coord c1, Coord c2) {  // plus
    return Coord{c1.x+c2.x, c1.y+c2.y};
  }
  friend Coord operator- (Coord c1, Coord c2) {  // diff
    return Coord{c1.x-c2.x, c1.y-c2.y};
  }
  Coord operator- () const {                     // negate
    return Coord{-x, -y};
  }
  void operator+= (Coord c) {                    // +=
    *this = *this + c;  // or: x+=c.x, y+=c.y
  }
  void operator-= (Coord c) {                    // +=
    operator+=(-c);     // or as above
  }

  int getX() const {
    return x;
  }
  int getY() const {
    return y;
  }

  friend std::ostream& operator<< (std::ostream& strm, Coord c) {
    return strm << '(' << c.x << ',' << c.y << ')';
  }
};

#endif

