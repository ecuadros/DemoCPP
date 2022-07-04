
// "inherit" all function call operators of passed base types:qa
template<typename ... Ts>
struct overload : Ts...
{
  using Ts::operator()...;
};

// base types are deduced from passed arguments:
template<typename ... Ts>
overload(Ts...) -> overload<Ts...>;

