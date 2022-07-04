
#include <utility>     // for std::forward()

template<typename CB>
class CountCalls
{
  private:
    CB callback;       // callback to call
    long calls = 0;    // counter for calls
  public:
    CountCalls(CB cb) : callback(cb) {}
    template<typename... Args>
    decltype(auto) operator() (Args&&... args)
    { ++calls;
      return callback(std::forward<Args>(args)...);
    }
    long count() const {  return calls; }
};

