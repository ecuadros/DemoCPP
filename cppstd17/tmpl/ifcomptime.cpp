#include <iostream>
#include "ifcomptime.hpp"
using namespace std;

#include <type_traits>

template< class T >
struct is_scalarx : integral_constant<bool,
                     is_arithmetic<T>::value     ||
                     is_enum<T>::value           ||
                     is_pointer<T>::value        ||
                     is_member_pointer<T>::value ||
                     is_null_pointer<T>::value> {};
                     
class A {};

int main()
{
  cout << asString(42) << '\n';
  cout << asString(string("hello")) << '\n';
  cout << asString("hello") << '\n';
  cout << asString(25.74) << '\n';

  cout << boolalpha
        << "A:           " << is_arithmetic_v<A>           << '\n' // false
        << "bool:        " << is_arithmetic_v<bool>        << '\n' // true
        << "int:         " << is_arithmetic_v<int>         << '\n' // true
        << "int const:   " << is_arithmetic_v<int const>   << '\n' // true
        << "int &:       " << is_arithmetic_v<int&>        << '\n' // false
        << "int *:       " << is_arithmetic_v<int*>        << '\n' // false
        << "float:       " << is_arithmetic_v<float>       << '\n' // true
        << "float const: " << is_arithmetic_v<float const> << '\n' // true
        << "float &:     " << is_arithmetic_v<float&>      << '\n' // false
        << "float *:     " << is_arithmetic_v<float*>      << '\n' // false
        << "char:        " << is_arithmetic_v<char>        << '\n' // true
        << "char const:  " << is_arithmetic_v<char const>  << '\n' // true
        << "char &:      " << is_arithmetic_v<char&>       << '\n' // false
        << "char *:      " << is_arithmetic_v<char*>       << '\n' // false
        ;

  class cls { public: int m1, m2; };
    cout << (is_scalarx<int>::value ? "T is a scalar" : "T is not a scalar") << '\n';
    cout << (is_scalarx<cls>::value ? "T is a scalar" : "T is not a scalar") << '\n';
  cls obj;
    cout << (is_object_v<cls> ? "T is an object" : "T is not an object") << '\n';
    cout << (is_object_v<decltype(obj)> ? "T is an object" : "T is not an object") << '\n';
  int x = 5;
    cout << (is_object<decltype(x)>::value ? "T is an object" : "T is not an object") << '\n';

  auto pm = &cls::m1;
  cout << (is_member_object_pointer<decltype(pm)>::value ? "T is a member function" : "T is not a member function") << '\n';
  cout << (is_member_object_pointer_v<int> ? "T is a member function" : "T is not a member function") << '\n';
  cout << (is_member_object_pointer_v<int cls::*> ? "T is a member function" : "T is not a member function") << '\n';
  auto &ref = x;
  cout << (is_reference<decltype(ref)>::value ? "T is a reference" : "T is not a reference") << '\n';
  cout << (is_reference<decltype( x )>::value ? "T is a reference" : "T is not a reference") << '\n';
}
