
#include <iostream>

template<decltype(auto) N>
struct S
{
  void printN() const
  {
    std::cout << "N: " << N << '\n';
  }
};

static const int c = 42;
static int v = 42;

int main()
{
  S<c> s1;      // deduces N as const int 42
  S<(c)> s2;    // deduces N as const int& referring to c
  s1.printN();
  s2.printN();
  
  S<(v)> s3;    // deduces N as int& referring to v
  v = 77;
  s3.printN();  // prints: N: 77
}

