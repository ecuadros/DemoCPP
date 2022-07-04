
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <functional>  // for the searchers
#if __has_include(<execution>)
#include <execution>   // for the execution policy
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

  // create a very big string:
  //  a b c d e ... z aa bb cc dd ee ... 
  std::string text;
  text.reserve(max*max*30);
  for (int i{1}; i<=max; ++i) {
    for (char c{'a'}; c<='z'; ++c) {
      for (int j{1}; j<=i; ++j) {
        text.push_back(c); 
      }
    }
  }

  // init the substring we search for (max times 'k'):
  std::string substr(max, 'k');
  std::cout << "search substring of " << max
            << " chars in string with " << text.size() << " chars\n"; 

  // init searchers for reuse:
  std::boyer_moore_searcher bm{substr.begin(), substr.end()};
  std::boyer_moore_horspool_searcher bmh{substr.begin(), substr.end()};

  // map to store measurements under a specific name:
  std::map<std::string, std::vector<double>> durs;

  // multiple measurements to make numbers mature:
  for (int i=0; i<5; ++i) {
    std::chrono::steady_clock::time_point t0, t1;
    std::string::iterator pos;

    // string member find():
    t0 = std::chrono::steady_clock::now();
    auto idx = text.find(substr);
    t1 = std::chrono::steady_clock::now();
    durs["find()"].push_back(diff(t0, t1));
    std::cout << "idx: " << idx << '\n'; 

    // search() algorithm:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(text.begin(), text.end(),
                      substr.begin(), substr.end());
    t1 = std::chrono::steady_clock::now();
    durs["search()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - text.begin() << '\n'; 

    // parallel search() algorithm:
#if __has_include(<execution>)
    t0 = std::chrono::steady_clock::now();
    pos = std::search(std::execution::par,
                      text.begin(), text.end(),
                      substr.begin(), substr.end());
    t1 = std::chrono::steady_clock::now();
    durs["par search()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - text.begin() << '\n'; 
#endif

    // default_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(text.begin(), text.end(),
                         std::default_searcher(substr.begin(), substr.end()));
    t1 = std::chrono::steady_clock::now();
    durs["search(def)"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - text.begin() << '\n'; 

    // boyer_moore_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(text.begin(), text.end(),
                         std::boyer_moore_searcher(substr.begin(), substr.end()));
    t1 = std::chrono::steady_clock::now();
    durs["search(bm)"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - text.begin() << '\n'; 

    // boyer_moore_horspool_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = std::search(text.begin(), text.end(),
                      std::boyer_moore_horspool_searcher(substr.begin(), substr.end()));
    t1 = std::chrono::steady_clock::now();
    durs["search(bmh)"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - text.begin() << '\n'; 

    // reused boyer_moore_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = bm(text.begin(), text.end()).first;
    t1 = std::chrono::steady_clock::now();
    durs["bm()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - text.begin() << '\n'; 

    // reused boyer_moore_horspool_searcher:
    t0 = std::chrono::steady_clock::now();
    pos = bmh(text.begin(), text.end()).first;
    t1 = std::chrono::steady_clock::now();
    durs["bmh()"].push_back(diff(t0, t1));
    std::cout << "idx: " << pos - text.begin() << '\n'; 
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

