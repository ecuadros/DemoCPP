
#include <type_traits> // for true_type, false_type, and void_t

// primary template:
template<typename, typename = std::void_t<>>
struct HasDelete
 : std::false_type {
};

// partial specialization (may be SFINAE'd away):
template<typename T>
struct HasDelete<T, std::void_t<decltype(T::operator delete(nullptr))>>
 : std::true_type {
};

