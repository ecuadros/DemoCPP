#include <iostream>
#include <vector>
#include <functional>
//#include "invoke.hpp"
#include "perfectreturn.hpp"

// g++ -pthread -std=c++17 -o main main.cpp demo.cpp
float w = 10.3;
float print(const vector<int>& coll)
{
  cout << "elems: ";
  for (const auto& elem : coll) {
    cout << elem << ' ';
  }
  cout << '\n';
  return ++w;
}

int main()
{
  vector<int> vals{0, 8, 15, 42, 13, -1, 0};
  call([&vals]() -> void
  {  cout << "size: " << vals.size() << '\n';
  });
  call([&vals](int a)
  {  cout << "size: " << vals.size() << ", a=" << a << '\n';
  }, 5);
  print(vals);
  auto w0 = call(print, vals);
  cout << "w0=" << w0 << endl;

  call(&decltype(vals)::pop_back, vals);    // vals.pop_back();
  auto w1 = call(print, vals);
  cout << "w1=" << w1 << endl;

  call(&decltype(vals)::clear, vals);       // vals.clear();
  auto w2 = call(print, vals);
  cout << "w2=" << w2 << endl;

  cout << "Type of vals: " << type_name<decltype(vals)>() << endl;
  cout << "Type of w2: " << type_name<decltype(w2)>() << endl;
}

