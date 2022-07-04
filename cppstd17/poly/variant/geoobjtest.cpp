
#include "geoobj.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <map>
#include "tracknew.hpp"
#include <variant>

using GOType = std::variant<Line, Circle, Polygon>;
using GOColl = std::vector<GOType>;


GOColl initColl(int num)
{
  GOColl coll;
  coll.reserve(num);

  for (int i=1; i < num/3 + 1; ++i) {
    Line l{"Line" + std::to_string(i),
           Coord{i,i}, Coord{100*i,100*i}};
    coll.push_back(l);
    Circle c{"Circle" + std::to_string(i),
             Coord{10*i,10*i}, i};
    coll.push_back(c);
    Polygon p{"Polygon" + std::to_string(i),
              {Coord{i,i}, Coord{i, -i},
               Coord{-i, -i}, Coord{-i, i}}};
    coll.push_back(p);
  }
  return coll;
}

void cleanColl(GOColl& coll)
{
  coll.clear();
}


long iterate(const GOColl& coll)
{
  long numEmpty = 0;
  for (const auto& go : coll) {
    std::visit([&numEmpty] (const auto& obj) {
                     if (obj.getName().empty()) {
                       ++numEmpty;
                     }
                   },
                   go);
  }
  return numEmpty;
}



long iterateDown(const GOColl& coll)
{
  long sumPoints = 0;
  for (const auto& go : coll) {
    if (auto p = std::get_if<Polygon>(&go); p != nullptr) {
      sumPoints += p->numPoints();
    }
  }
  return sumPoints;
}


class NumPoints {
  private:
    long sumPoints{0};
  public:
    void operator() (const Polygon& p) {
      sumPoints += p.numPoints();
    }
    template <typename T>
    void operator() (const T&) {
    }
    long getSum() const {
      return sumPoints;
    }
};

long iterateDown2(const GOColl& coll)
{
  NumPoints fo;
  for (const auto& go : coll) {
    std::visit(fo, go);
  }
  return fo.getSum();
}


void shuffleAndMod(GOColl& coll)
{
  std::default_random_engine dre;
  std::shuffle(coll.begin(), coll.end(),  // range
               dre);                // random number generator

  for (auto& go : coll) {
    std::visit([] (auto& obj) {
                 obj.move(Coord{0,1});
               },
               go);
  }
}

void sort(GOColl& coll)
{
  /*
  auto getName = [] (const auto& obj) { return obj.getName(); };
  std::sort(coll.begin(), coll.end(),
            [getName] (const auto& go1, const auto& go2) {
              return std::visit(getName, go1) < std::visit(getName, go2);
            });
  */
  auto getName = [](const auto& go) {
                   return std::visit([] (const auto& obj) { return obj.getName(); },
                                     go);
                 };
  std::sort(coll.begin(), coll.end(),
            [getName] (const auto& go1, const auto& go2) {
              return getName(go1) < getName(go2);
            });
}

void copy(const GOColl& coll)
{
  GOColl coll2{coll};
  assert(coll.size() == coll2.size());
  //std::cout << "     ";
  //std::visit([] (const auto& obj) {
  //             obj.draw();
  //           },
  //           coll[coll.size()-1]);
}

void covariant(const GOColl& coll)
{
  for (const auto& go : coll) {
    auto g = go;
    assert((std::is_same_v<decltype(g), GOType>));
    //...  // e.g. std::visit(..., g);
    // no need to call delete
  }
}


int main(int argc, const char** argv)
{
  int num = 10000;
  if (argc > 1) {
    num = std::atoi(argv[1]);
  }

  std::cout << "***********************************************\n";
  std::map<std::string, std::chrono::duration<double,std::milli>> data;
  const int numLoops = 10;
  int numMeasured = 0;
  for (int i=0; i<numLoops; ++i) {
    TrackNew::reset();
    auto t1a = std::chrono::high_resolution_clock::now();
    auto coll = initColl(num);
    auto t1b = std::chrono::high_resolution_clock::now();
    auto d1 = std::chrono::duration<double, std::milli>(t1b-t1a);
    std::cout << "**** initColl():      " << d1.count() << " ms\n";

    auto t2a = std::chrono::high_resolution_clock::now();
    shuffleAndMod(coll);
    auto t2b = std::chrono::high_resolution_clock::now();
    auto d2 = std::chrono::duration<double, std::milli>(t2b-t2a);
    std::cout << "**** shuffleAndMod(): " << d2.count() << " ms\n";

    auto t3a = std::chrono::high_resolution_clock::now();
    sort(coll);
    auto t3b = std::chrono::high_resolution_clock::now();
    auto d3 = std::chrono::duration<double, std::milli>(t3b-t3a);
    std::cout << "**** sort():          " << d3.count() << " ms\n";

    auto t4a = std::chrono::high_resolution_clock::now();
    copy(coll);
    auto t4b = std::chrono::high_resolution_clock::now();
    auto d4 = std::chrono::duration<double, std::milli>(t4b-t4a);
    std::cout << "**** copy()           " << d4.count() << " ms\n";

    auto t5a = std::chrono::high_resolution_clock::now();
    auto numEmpty = iterate(coll);
    auto t5b = std::chrono::high_resolution_clock::now();
    auto d5 = std::chrono::duration<double, std::milli>(t5b-t5a);
    std::cout << "**** iterate():):     " << d5.count() << " ms\n";
    std::cout << "                      " << numEmpty << " empty names\n";

    auto t6a = std::chrono::high_resolution_clock::now();
    auto numPoints = iterateDown(coll);
    auto t6b = std::chrono::high_resolution_clock::now();
    auto d6 = std::chrono::duration<double, std::milli>(t6b-t6a);
    std::cout << "**** iterateDown():   " << d6.count() << " ms\n";
    std::cout << "                      " << numPoints << " points\n";

    auto t7a = std::chrono::high_resolution_clock::now();
    covariant(coll);
    auto t7b = std::chrono::high_resolution_clock::now();
    auto d7 = std::chrono::duration<double, std::milli>(t7b-t7a);
    std::cout << "**** covariant():):     " << d7.count() << " ms\n";

    auto t8a = std::chrono::high_resolution_clock::now();
    cleanColl(coll);
    auto t8b = std::chrono::high_resolution_clock::now();
    auto d8 = std::chrono::duration<double, std::milli>(t8b-t8a);
    std::cout << "**** cleanColl():     " << d8.count() << " ms\n";

    auto d = std::chrono::duration<double, std::milli>(t8b-t1a);
    std::cout << "---------- ";
    TrackNew::status();

    if (numLoops > 0) {
      ++numMeasured;
      data["a: initColl():      "] += d1;
      data["b: cleanColl():     "] += d8;
      data["c: iterate():       "] += d5;
      data["d: iterateDown():   "] += d6;
      data["e: shuffleAndMod(): "] += d2;
      data["f: sort():          "] += d3;
      data["g: copy()           "] += d4;
      data["h: covariant():     "] += d7;
      data["i: ALL:             "] += d;
    }
  }
  std::cout << "***********************************************\n";
  for (const auto& d : data) {
    std::cout << "  " << d.first << d.second.count() / numMeasured << "ms\n";
  }
  std::cout << "sizeof(GOType):       " << sizeof(GOType) << '\n';
}

