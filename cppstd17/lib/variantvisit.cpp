
#include <variant>
#include <string>
#include <iostream>

struct MyVisitor
{
  void operator() (int i) const {
    std::cout << "int:    " << i << '\n';
  }
  void operator() (std::string s) const {
    std::cout << "string: " << s << '\n';
  }
  void operator() (long double d) const {
    std::cout << "double: " << d << '\n';
  }
};

int main()
{
  std::variant<int, std::string, double> var(42);
  std::visit(MyVisitor(), var);  // calls operator() for int
  var = "hello";
  std::visit(MyVisitor(), var);  // calls operator() for string
  var = 42.7;
  std::visit(MyVisitor(), var);  // calls operator() for long double
}

