
#include "customer2.hpp"
#include <utility>  // for tuple-like API

// provide a tuple-like API for class Customer for structured bindings:
template<>
struct std::tuple_size<Customer> {
  static constexpr int value = 3;   // we have 3 attributes
};

template<>
struct std::tuple_element<2, Customer> {
  using type = long;                // last attribute is a long
};
template<std::size_t Idx>
struct std::tuple_element<Idx, Customer> {
  using type = std::string;         // the other attributes are strings
};

// define specific getters:
template<std::size_t I> decltype(auto) get(Customer& c) {
  static_assert(I < 3);
  if constexpr (I == 0) {
    return c.firstname();
  }
  else if constexpr (I == 1) {
    return c.lastname();
  }
  else {  // I == 2
    return c.value();
  }
}   
template<std::size_t I> decltype(auto) get(const Customer& c) {
  static_assert(I < 3);
  if constexpr (I == 0) {
    return c.firstname();
  }
  else if constexpr (I == 1) {
    return c.lastname();
  }
  else {  // I == 2
    return c.value();
  }
}   
template<std::size_t I> decltype(auto) get(Customer&& c) {
  static_assert(I < 3);
  if constexpr (I == 0) {
    return std::move(c.firstname());
  }
  else if constexpr (I == 1) {
    return std::move(c.lastname());
  }
  else {  // I == 2
    return c.value();
  }
}   

