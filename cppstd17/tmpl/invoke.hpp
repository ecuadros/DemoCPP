
#include <utility>     // for invoke()
#include <functional>  // for forward()
using namespace std;

#include <string_view>

template <typename T>
constexpr auto type_name()
{
  string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

template <typename R, typename ... Args>
R getRetType (R (*)(Args...));

int c = 0;
template<typename Callable, typename... Args>
auto call1(Callable&& op, Args&&... args)
{
  cout << ++c << ": ";
  //using R = invoke_result<Callable, Args...>;
  /*if( is_void_v<R> )
    cout << "Function is returning: void!";
  else
  {*/ 
  return invoke(forward<Callable>(op),    // call passed callable with
                forward<Args>(args)...);        // all additional passed args
  //cout << "Function is returning: " << type_name<decltype(ret)>() << "\n"; // << decltype(R);
  //  return ret;
  //}
  
}

