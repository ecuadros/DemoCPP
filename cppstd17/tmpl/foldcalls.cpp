
#include <iostream>

// template for variadic number of base classes
template<typename... Bases>
class MultiBase : private Bases...
{
  public:
    void print()
    {
      // call print() of all base classes:
      (... , Bases::print());
    }
};

struct A
{  void print() { std::cout << "A::print()\n"; }
};

struct B
{  void print() { std::cout << "B::print()\n"; }
};

struct C
{  void print() { std::cout << "C::print()\n"; }
};

int main()
{
    MultiBase<A,B,C> mb;
    mb.print();
}

