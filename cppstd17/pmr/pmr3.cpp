
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>  // for std::byte
#include <memory_resource>
#include "../lang/tracknew.hpp"

int main()
{
  // allocate some memory on the stack:
  std::array<std::byte, 200000> buf;

  for (int num : {1000, 2000, 500, 2000, 3000, 50000, 1000}) {
    std::cout << "-- check with " << num << " elements:\n";
    TrackNew::reset();

    std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
    std::pmr::vector<std::pmr::string> coll{&pool};
    for (int i=0; i < num; ++i) {
      coll.emplace_back("just a non-SSO string");
    }

    TrackNew::status();
  }
}

