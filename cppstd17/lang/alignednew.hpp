
#include <cstddef>   // for std::size_t
#include <new>       // for std::align_val_t
#include <cstdlib>   // for malloc(), aligned_alloc(), free()
#include <string>

struct alignas(32) MyType32 {
  int i;
  char c;
  std::string s[4];
  //...
  static void* operator new (std::size_t size) {
    // called for default-aligned data:
    std::cout << "MyType32::new() with size " << size << '\n';
    return ::operator new(size);
  }
  static void* operator new (std::size_t size, std::align_val_t align) {
    // called for over-aligned data:
    std::cout << "MyType32::new() with size " << size
              << " and alignment " << static_cast<std::size_t>(align)
              << '\n';
    return ::operator new(size, align);
  }

  static void operator delete (void* p) {
    // called for default-aligned data:
    std::cout << "MyType32::delete() without alignment\n";
    ::operator delete(p);
  }
  static void operator delete (void* p, std::size_t size) {
    MyType32::operator delete(p);         // use the non-sized delete
  }
  static void operator delete (void* p, std::align_val_t align) {
    // called for default-aligned data:
    std::cout << "MyType32::delete() with alignment\n";
    ::operator delete(p, align);
  }
  static void operator delete (void* p, std::size_t size,
                                        std::align_val_t align) {
    MyType32::operator delete(p, align);  // use the non-sized delete
  }

  // also for arrays (operator new[] and operator delete[])
  //...
};

