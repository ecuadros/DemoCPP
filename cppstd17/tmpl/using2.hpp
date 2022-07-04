template<typename T>
class Base 
{
    T value{};
  public:
    Base()
    {  //...
    }
    Base(T v) : value{v} {
      //...
    }
    //...
};

template<typename... Types>
class Multi : private Base<Types>...
{
  public:
    // derive all constructors:
    using Base<Types>::Base...;
    //...
};
