
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <chrono>
#include <functional>  // for the searchers
#if __has_include(<execution>)
#include <execution>  // for the execution policy
#endif

template <typename T>
double diff(const T& t0, const T& t1)
{
  return std::chrono::duration<double,std::milli>(t1 - t0).count();
}


int main(int argc, char* argv[])
{
  // command-line argument to init the maximum sequence of equal characters:
  int max = 1000;
  if (argc > 1) {
    max = atoi(argv[1]);
  }

  // create a very big vector:
  //  0 1 2 3 4 ... 9 00 11 22 33 44 ... 
  std::vector<int> coll;
  coll.reserve(max*max*10);
  for (int i{1}; i<=max; ++i) {
    for (int v{0}; v<=9; ++v) {
      for (int j{1}; j<=i; ++j) {
        coll.push_back(v);
      }
    }
  }

  // init the subsequence we search for (max times '4'):
  std::deque<int> sub(max, 4);
  std::cout << "search sequence of " << max
            << " ints in vector with " << coll.size() << " ints\n"; 

  // init searchers for reuse:
  std::boyer_moore_searcher bm{sub.begin(), sub.end()};
  std::boyer_moore_horspool_searcher bmh{sub.begin(), sub.end()};

  // map to store measurements under a specific name:
  std::map<std::string, std::vector<double>> durs;

  // multiple measurements to make numbers mature:
  for (int i=0; i<5; ++i) {
    std::chrono::steady_clock::time_point t0, t1;
    std::vector<int>::iterator pos;

    // search() algorithm:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(coll.begin(), coll.end(),
                      sub.begin(), sub.end());
    t1 = std::chrono::steady_clock::now();
    durs["search()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - coll.begin() << '\n'; 

    // parallel search() algorithm:
#if __has_include(<execution>)
    t0 = std::chrono::steady_clock::now();
    pos = std::search(std::execution::par,
                      coll.begin(), coll.end(),
                      sub.begin(), sub.end());
    t1 = std::chrono::steady_clock::now();
    durs["par search()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - coll.begin() << '\n'; 
#endif

    // default_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(coll.begin(), coll.end(),
                         std::default_searcher(sub.begin(), sub.end()));
    t1 = std::chrono::steady_clock::now();
    durs["search(def)"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - coll.begin() << '\n'; 

    // boyer_moore_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(coll.begin(), coll.end(),
                         std::boyer_moore_searcher(sub.begin(), sub.end()));
    t1 = std::chrono::steady_clock::now();
    durs["search(bm)"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - coll.begin() << '\n'; 

    // boyer_moore_horspool_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(coll.begin(), coll.end(),
                      std::boyer_moore_horspool_searcher(sub.begin(), sub.end()));
    t1 = std::chrono::steady_clock::now();
    durs["search(bmh)"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - coll.begin() << '\n'; 

    // reused boyer_moore_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = bm(coll.begin(), coll.end()).first;
    t1 = std::chrono::steady_clock::now();
    durs["bm()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - coll.begin() << '\n'; 

    // reused boyer_moore_horspool_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = bmh(coll.begin(), coll.end()).first;
    t1 = std::chrono::steady_clock::now();
    durs["bmh()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - coll.begin() << '\n'; 
  }

  // print measurements:
  for (const auto& elem : durs) {
    std::cout << "\n" << elem.first << ": ";
    double avg = 0;
    for (const auto& val : elem.second) {
      std::cout << val << " ";
      avg += val;
    }
    std::cout << "ms\n";
    std::cout << "  avg: " << avg / elem.second.size() << "ms\n";
  }
}

