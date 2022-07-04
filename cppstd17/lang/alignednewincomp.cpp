
#include <cstddef>   // for std::size_t
#include <cstdlib>   // for std::malloc()
#include <cstdio>    // for std::printf()

void* operator new (std::size_t size)
{
  std::printf("::new called with size: %zu\n", size);
  return ::std::malloc(size);
}

int main()
{
  struct alignas(64) S {
    int i;
  };

  S* p = new S;  // calls our operator new only before C++17
}

