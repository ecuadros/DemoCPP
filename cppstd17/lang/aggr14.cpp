
struct Derived;

struct Base {
 friend struct Derived;
 private: 
  Base() {
  }
};

struct Derived : Base {
};

int main()
{
  Derived d1{};    // ERROR since C++17
  Derived d2;      // still OK (but might not initialize)
}

