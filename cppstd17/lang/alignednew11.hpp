
#include <cstddef>   // for std::size_t
#include <string>
#if __STDC_VERSION >= 201112L
#include <stdlib.h>  // for aligned_alloc()
#else
#include <malloc.h>  // for _aligned_malloc() or memalign()
#endif

struct alignas(32) MyType32 {
  int i;
  char c;
  std::string s[4];
  //...
  static void* operator new (std::size_t size) {
      // allocate memory for requested alignment:
#if __STDC_VERSION >= 201112L
      // use API of C11:
      return aligned_alloc(alignof(MyType32), size);
#else
#ifdef _MSC_VER
      // use API of Windows:
      return _aligned_malloc(size, alignof(MyType32));
#else
      // use API of Linux:
      return memalign(alignof(MyType32), size);
#endif
#endif
  }

  static void operator delete (void* p) {
      // deallocate memory for requested alignment:
#ifdef _MSC_VER
      // use special API of Windows:
      _aligned_free(p);
#else
      // C11/Linux can use the general free():
      free(p);
#endif
  }
  // since C++14:
  static void operator delete (void* p, std::size_t size) {
      MyType32::operator delete(p);  // use the non-sized delete
  }
  //...
  // also for arrays (new[] and delete[])
};

