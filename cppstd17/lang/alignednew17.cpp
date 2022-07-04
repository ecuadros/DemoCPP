
#include <string>

struct alignas(32) MyType32 {
  int i;
  char c;
  std::string s[4];
  //...
};

int main()
{
  auto p = new MyType32;  // allocates 32-byte aligned memory since C++17
  //...
  delete p;
}

