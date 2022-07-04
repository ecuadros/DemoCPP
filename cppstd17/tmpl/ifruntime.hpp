
#include <string>

template <typename T>
std::string asString(T x)
{
  if (std::is_same_v<T, std::string>) {
    return x;                  // ERROR if no conversion to string
  }
  else if (std::is_numeric_v<T>) {
    return std::to_string(x);  // ERROR if x is not numeric
  }
  else {
    return std::string(x);     // ERROR if no conversion to string
  }
}

