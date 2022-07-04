
#include <string>
using namespace std;

template <typename T>
string asString(T x)
{
  if constexpr(is_same_v<T, string>)
    return x;                  // statement invalid if no conversion to string
  else if constexpr(is_arithmetic_v<T>)
    return to_string(x);  // statement invalid if x is not numeric
  else
    return string(x);     // statement invalid if no conversion to string
}

