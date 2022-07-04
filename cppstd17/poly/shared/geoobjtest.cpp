
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
#include <memory>      // for std::shared_ptr<>


using GOType = std::shared_ptr<GeoObj>;
using GOColl = std::vector<GOType>;


GOColl initColl(int num)
{
  GOColl coll;
  coll.reserve(num);

  for (int i=1; i < num/3 + 1; ++i) {
    auto lp = std::make_shared<Line>("Line" + std::to_string(i),
                                     Coord{i,i}, Coord{100*i,100*i});
    coll.push_back(lp);
    auto cp = std::make_shared<Circle>("Circle" + std::to_string(i),
                                       Coord{10*i,10*i}, i);
    coll.push_back(cp);
    auto pp = std::make_shared<Polygon>("Polygon" + std::to_string(i),
                                        std::initializer_list<Coord>{
                                         Coord{i,i}, Coord{i, -i},
                                         Coord{-i, -i}, Coord{-i, i}});
    coll.push_back(pp);
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
    if (go->getName().empty()) {
      ++numEmpty;
    }
  }
  return numEmpty;
}

long iterateDown(const GOColl& coll)
{
  long sumPoints = 0;
  for (const auto& go : coll) {
    if (auto p = std::dynamic_pointer_cast<const Polygon>(go); p != nullptr) {
      sumPoints += p->numPoints();
    }
  }
  return sumPoints;
}


void shuffleAndMod(GOColl& coll)
{
  std::default_random_engine dre;
  std::shuffle(coll.begin(), coll.end(),  // range
               dre);                // random number generator

  for (auto& go : coll) {
    go->move(Coord{0,1});
  }
}

void sort(GOColl& coll)
{
  std::sort(coll.begin(), coll.end(),
            [] (const auto& p1, const auto& p2) {
              return p1->getName() < p2->getName();
            });
}

void copy(const GOColl& coll)
{
  GOColl coll2{coll};
  assert(coll.size() == coll2.size());
  //std::cout << "     ";
  //coll[coll.size()-1]->draw();
}

void covariant(const GOColl& coll)
{
  for (const auto& go : coll) {
    auto gp{go->clone()};
    assert((std::is_same_v<decltype(gp), std::shared_ptr<GeoObj>>));
    //...  // e.g. gp->draw()
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
    auto sumEmpty = iterate(coll);
    auto t5b = std::chrono::high_resolution_clock::now();
    auto d5 = std::chrono::duration<double, std::milli>(t5b-t5a);
    std::cout << "**** iterate():):     " << d5.count() << " ms\n";
    std::cout << "                      " << sumEmpty << " empty names\n";

    auto t6a = std::chrono::high_resolution_clock::now();
    auto sumPoints = iterateDown(coll);
    auto t6b = std::chrono::high_resolution_clock::now();
    auto d6 = std::chrono::duration<double, std::milli>(t6b-t6a);
    std::cout << "**** iterateDown():   " << d6.count() << " ms\n";
    std::cout << "                      " << sumPoints << " points\n";

    auto t7a = std::chrono::high_resolution_clock::now();
    covariant(coll);
    auto t7b = std::chrono::high_resolution_clock::now();
    auto d7 = std::chrono::duration<double, std::milli>(t7b-t7a);
    std::cout << "**** covariant():):   " << d7.count() << " ms\n";

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

