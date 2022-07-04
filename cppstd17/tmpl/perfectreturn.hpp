
#include <functional>   // for forward()
#include <type_traits>  // for is_same<> and invoke_result<>
using namespace std;

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

template<typename Callable, typename... Args>
decltype(auto) call(Callable op, Args&&... args)
{
  if constexpr(is_void_v<invoke_result_t<Callable, Args...>>)
  { cout << "Function is returning: void!" << endl;
    invoke(forward<Callable>(op), forward<Args>(args)...);
    //...  // do something before we return
    return;
  }
  else // return type is not void:
  { auto ret = invoke(forward<Callable>(op), forward<Args>(args)...);
    cout << "Function is returning: " << type_name<decltype(ret)>() << endl;
    //...  // do something (with ret) before we return
    return ret;
  }
}

