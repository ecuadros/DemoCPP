
#include <type_traits>

// check whether passed types are homogeneous:
template<typename T1, typename... TN>
struct IsHomogeneous {
  static constexpr bool value = (std::is_same_v<T1,TN> && ...);
};

// check whether passed arguments have the same type:
// Just testing comments
template<typename T1, typename... TN>
constexpr bool isHomogeneous(T1, TN...)
{
  return (std::is_same_v<T1,TN> && ...);
}

