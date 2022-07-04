
#include <iostream>
#include <string>
#include <memory_resource>

class Tracker : public std::pmr::memory_resource
{
 private:
  std::pmr::memory_resource* upstream;  // wrapped memory resource
  std::string prefix{};
 public:
  // we wrap the passed or default resource:
  explicit Tracker(std::pmr::memory_resource* us
                    = std::pmr::get_default_resource())
   : upstream{us} {
  }
  explicit Tracker(std::string p,
                   std::pmr::memory_resource* us
                    = std::pmr::get_default_resource())
   : prefix{std::move(p)}, upstream{us} {
  }
 private:
  void* do_allocate(size_t bytes, size_t alignment) override {
    std::cout << prefix << "allocate " << bytes << " Bytes\n";
    void* ret = upstream->allocate(bytes, alignment);
    return ret;
  }
  void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
    std::cout << prefix << "deallocate " << bytes << " Bytes\n";
    upstream->deallocate(ptr, bytes, alignment);
  }
  bool do_is_equal(const std::pmr::memory_resource& other) const noexcept
   override {
    // same object?:
    if (this == &other) return true;
    // same type and prefix and equal upstream?:
    auto op = dynamic_cast<const Tracker*>(&other);
    return op != nullptr && op->prefix == prefix
            && upstream->is_equal(other);
  }
};

