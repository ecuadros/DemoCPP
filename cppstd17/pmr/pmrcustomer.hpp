
#include <string>
#include <memory_resource>

// Customer as polymorphic-allocator-aware type
// - the allocator is stored in the string member
class PmrCustomer
{
 private:
  std::pmr::string name;  // also used to store the allocator
 public:
  using allocator_type = std::pmr::polymorphic_allocator<char>; 

  // initializing constructor(s):
  PmrCustomer(std::pmr::string n, allocator_type alloc = {})
   : name{std::move(n), alloc} {
  }

  // copy/move with allocators:
  PmrCustomer(const PmrCustomer& c, allocator_type alloc)
   : name{c.name, alloc} {
  }
  PmrCustomer(PmrCustomer&& c, allocator_type alloc)
   : name{std::move(c.name), alloc} {
  }

  // setters/getters:
  void setName(std::pmr::string s) {
    name = std::move(s);
  }
  std::pmr::string getName() const {
    return name;
  }
  std::string getNameAsString() const {
    return std::string{name};
  }
};

