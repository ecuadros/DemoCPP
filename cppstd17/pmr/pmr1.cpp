
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>  // for std::byte
#include <memory_resource>
#include "../lang/tracknew.hpp"

int main()
{
  TrackNew::reset();

  // allocate some memory on the stack:
  std::array<std::byte, 200000> buf;

  // and use it as initial memory pool for a vector:
  std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
  std::pmr::vector<std::string> coll{&pool};

  for (int i=0; i < 1000; ++i) {
    coll.emplace_back("just a non-SSO string");
  }

  TrackNew::status();
}

