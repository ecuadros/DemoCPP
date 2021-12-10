
#include <iostream>
#include <bitset>
#include <vector>
#include <array>
#include <utility>     // for forward()
#include <fstream>
#include <chrono>

#include <optional>
#include <string_view>
#include <charconv>     // for from_chars()
 #include <map>

#include <variant>

#include "demo.h"
#include "linkedlist.h"
#include "doublelinkedlist.h"
#include "types.h"
#include "recorrer.h"
#include "../../cppstd17/tmpl/foldtraverse.hpp"
#include "../../cppstd17/tmpl/ishomogeneous.hpp"

using namespace std;

// Functions for DemoInvoke
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

// From tmplbook/inherit/countertest.cpp
#include "objectcounter.hpp"
template<typename CharT>
class MyString : public ObjectCounter<MyString<CharT>> 
{
  //...
};

void CounterTest()
{
  MyString<char> s1, s2;
  MyString<wchar_t> ws;
  std::cout << "num of MyString<char>:    " << MyString<char>::live() << '\n';
  std::cout << "num of MyString<wchar_t>: " << ws.live() << '\n';
  if( true )
  {
    MyString<char> s3;
    std::cout << "num of MyString<char>:    " << MyString<char>::live() << '\n';
  }
  std::cout << "num of MyString<char>:    " << MyString<char>::live() << '\n';
}

// From tmplbook/overload/initlist.cpp
#include <initializer_list>
#include <string>
#include <vector>
#include <complex>
#include <iostream>

void f(std::initializer_list<int>)
{  std::cout << "#1 initializer_list<int>\n\n";
}

void f(std::initializer_list<std::string>)
{  std::cout << "#2 initializer_list<std::string>\n\n";
}

void g(std::vector<int> const& vec)
{  std::cout << "#3 vector<int> const& vec\n\n";
}

void h(std::complex<double> const& cmplx)
{  std::cout << "#4 complex<double> const& cmplx\n\n";
}

struct Point
{  int x, y;
};

void i(Point const& pt)
{  std::cout << "#5 Point const& pt\n\n";
}

void DemoInitializer1()
{
  std::cout << "{1, 2, 3} \n";
  f({1, 2, 3});                         // prints \#1
  std::cout << "{\"hello\", \"initializer\", \"list\"}\n";
  f({"hello", "initializer", "list"});  // prints \#2
  std::cout << "{1, 1, 2, 3, 5} \n";
  g({1, 1, 2, 3, 5});                   // prints \#3
  std::cout << "{1.5, 2.5} \n";
  h({1.5, 2.5});                        // prints \#4
  std::cout << "{1, 2} \n";
  i({1, 2});                            // prints \#5
}

// From tmplbook/overload/initlistctor.cpp
#include <initializer_list>
#include <string>
#include <iostream>

template<typename T>
struct Array
{
    Array(std::initializer_list<T>)
    {  std::cout << "#1 initializer_list<T>\n\n";  }

    Array(unsigned n, T const&)
    {  std::cout << "#2 unsigned n, T const&\n\n";  }
};

void arr1(Array<int>        ){}
void arr2(Array<std::string>){}

void DemoInitializer2()
{
    std::cout << "{1, 2, 3, 4, 5}\n";
    arr1({1, 2, 3, 4, 5});                     // prints \#1
    std::cout << "{1, 2}\n";
    arr1({1, 2});                              // prints \#1
    std::cout << "{10u, 5}\n";
    arr1({10u, 5});                            // prints \#1
    std::cout << "{\"hello\", \"initializer\", \"list\"}\n";
    arr2({"hello", "initializer", "list"});    // prints \#1
    std::cout << "{10, \"hello\"}\n";
    arr2({10, "hello"});                       // prints \#2
}

// From tmplbook/overload/initlistovl.cpp
#include <initializer_list>
#include <iostream>

void ovl(std::initializer_list<char>) // \#1
{ std::cout << "#1 initializer_list<char>\n\n"; 
}

void ovl(std::initializer_list<int>)  // \#2
{ std::cout << "#2 initializer_list<int>\n\n";
}

void DemoInitializer3()
{
  std::cout << "{'h', 'e', 'l', 'l', 'o', '\\0'}\n";
  ovl({'h', 'e', 'l', 'l', 'o', '\0'});  // prints \#1
  std::cout << "{'h', 'e', 'l', 'l', 'o', 0}\n";
  ovl({'h', 'e', 'l', 'l', 'o', 0});     // prints \#2
}

auto foo()
{
    struct retVals        // Declare a local structure 
    { int i1, i2;
      string str;
    };
    return make_tuple(10, 20, "Hi", 5.4, 8.2); // Return the 
}

void DemoMultipleParams()
{
    auto [v1, v2, v3, v4, v5] = foo(); // structured binding declaration
    cout << v1 << ", " << v2 << ", " << v3 << ", " << v4 << ", " << v5 << endl;
}

// From tmplbook/details/tupleoverload.cpp
template<typename... Ts>
class Tuple
{
};

template<typename T>
std::string f(Tuple<T*>)
{
    return "f(Tuple<T*>)";
}

template<typename... Ts>
std::string f(Tuple<Ts...>)
{
    return "f(Tuple<Ts...>)";
}

template<typename... Ts>
std::string f(Tuple<Ts*...>)
{
    return "f(Tuple<Ts*...>)";
}

void DemoTupleOverload()
{
    std::cout << "f(Tuple<int, double>())   -> " << f(Tuple<int, double>())    << endl;  // calls f<>(Tuple<Ts...>)
    std::cout << "f(Tuple<int*, double*>()) -> " << f(Tuple<int*, double*>())  << endl;  // calls f<>(Tuple<Ts*...>)
    std::cout << "f(Tuple<int*>())          -> " << f(Tuple<int*>())           << endl;  // calls f<>(Tuple<T*>)
}

// From tmplbook/details/variadicoverload.cpp
template<typename T>
std::string fw(T *)
{ return "f<>(T *)";       }

template<typename... Ts>
std::string fw(Ts...)
{  return "f<>(Ts ...)";   }

template<typename... Ts>
std::string fw(Ts*...)
{  return "f<>(Ts *...)";  }

void DemoVariadicOverload()
{
  std::cout << "fw(0, 0.0)                          -> " 
            << fw(0, 0.0) << endl;                          // calls f<>(Ts...)
  std::cout << "fw((int*)nullptr, (double*)nullptr) -> "
            << fw((int*)nullptr, (double*)nullptr) << endl; // calls f<>(Ts*...)
  std::cout << "fw((int*)nullptr                    -> " 
            << fw((int*)nullptr) << endl;                   // calls f<>(T*)
}

float print(const vector<int>& coll)
{
    cout << "elems: ";
    for (const auto& elem : coll)
    {  cout << elem << ' '; }
    cout << '\n';
    return 0.0;
}

auto sum1()
{
    return 0;
}

template <typename T, typename... Q>
auto sum1(T arg1, Q ... args)
{
    return arg1 + sum1(args...);
}

template <typename ... T>
auto sum2(T ... args)
{
    return (... + args);
}

template <typename... T>
auto sum3(T ... args)
{
    return (... + args);
}

template <typename... T>
auto print1(T ... args)
{
    (cout << ... << args) << "fin!\n";
}

template <typename... T>
auto print2(T ... args)
{
    cout << (args << ...);
}

template<typename T>
const T& spaceBefore(const T& arg)
{   cout << ' ';
    return arg;
}

template <typename First, typename... Args>
void printx(const First& firstarg, const Args&... args)
{
    cout << firstarg;
    (cout << ... << spaceBefore(args)) << '\n';
}

template <typename First, typename... Args>
void printy(const First& firstarg, const Args&... args)
{
    cout << firstarg;
    auto spaceBeforex = [](const auto& arg) -> const auto&
    { cout << ' ';
      return arg;
    };
    (cout << ... << spaceBeforex(args)) << '\n';
}

template <std::size_t ... idx, typename Container>
void printIdx(const Container& coll)
{
    printx(coll[idx]...);
}

template <typename Container, typename... Idx>
void printIdx2(const Container& coll, const Idx&... idx)
{
    printx(idx...);
    printx(coll[idx]...);
}

/*template <typename Container>
void printIdx3(const Container& coll, std::size_t ... idx)
{
     printIdx<idx...>(coll);
}*/

void demoVariadic()
{
    auto rpta1 = sum1(7, 5, 3, 10);
    cout << rpta1 << endl;

    auto rpta2 = sum2(6, 8, 2.5, 10);
    cout << rpta2 << endl;

    auto rpta3 = sum3(6, 8, 7.5, 10);
    cout << rpta3 << endl;

    auto rpta4 = sum2(string("Hola"), "que", "tal! ", "prueba ", "de", "variadic", "templates");
    cout << rpta4 << endl;

    //auto rpta5 = sum2("Hola", "que", "tal! ", "prueba ", "de ", "variadic ", "templates ");
    //cout << rpta5 << endl;
    print1("Holax", "quex", "tal! ", "prueba ", "de ", "variadic ", "templates ");

    std:vector<std::string> strVect = {"Hello", "testing", "variadic", "indices", "in", "C++17"};
    printIdx<1, 3, 5, 0>(strVect);
    printIdx2(strVect, 1, 3, 5, 0);
    //printIdx3(strVect, 1, 3, 5, 0); // Error Pending
}

void DemoFoldedFunctions()
{
    printx("Holax", "quex", "tal!", "prueba", "de", "variadic", "templates");
    printy("Holax", "quex", "tal!", 5, 'z', "prueba", "de", "variadic", "templates");
}

template<typename T1, typename... TN>
void __DemoHomogeneous(T1, TN...)
{
    if( IsHomogeneous<T1, TN...>::value )
      cout << "Homogeneous ..." << endl;
    else
      cout << "NOT Homogeneous ..." << endl;
}

void DemoHomogeneous()
{
    int x = 5, y = 6, z = 9;
    short s1 = 75;
    float f1 = 9.3, f2 = 7.2;
    __DemoHomogeneous(x, y, z);
    __DemoHomogeneous(f1, f2);
    __DemoHomogeneous(f1, x, y);
    __DemoHomogeneous(s1, x, y);
}

// From foldcalls.cpp
// template for variadic number of base classes
template<typename... Bases>
class MultiBase : private Bases ...
{
  public:
    void print()
    {
      // call print() of all base classes:
      (... , Bases::print());
      (cout << ... << type_name<Bases>() ) << endl;
      (cout << ... << spaceBefore( type_name<Bases>() ) ) << endl;
    }
};

struct A1
{  void print() { cout << "A1::print()\n"; }
};

struct B1
{  void print() { cout << "B1::print()\n"; }
};

struct C1
{  void print() { cout << "C1::print()\n"; }
};

void DemoMultiBase1()
{
    MultiBase<A1,B1,C1> mb1;
    mb1.print();
    
    MultiBase<A1,C1> mb2;
    mb2.print();
}

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
    Multi() : Base<Types>()... {} // Added by Er
    // derive all constructors:
    using Base<Types>::Base...;
    //...
};

void DemoMultiBase2()
{
    Multi<A1,B1,C1> mb1;
    //mb1.print();
    
    Multi<A1,C1> mb2;
    //mb2.print();
}

// From tmplbook/inherit/virtual.cpp
#include <iostream>

class NotVirtual
{
};

class Virtual
{
  public:
    virtual void foo() {}
};

template<typename... Mixins>
class BaseC : public Mixins...
{
  public:
    // the virtuality of foo() depends on its declaration
    // (if any) in the base classes Mixins...
    void foo()
    {
       std::cout << "BaseC::foo()" << '\n';
    }
};

template<typename... Mixins>
class Derived : public BaseC<Mixins...>
{
  public:
    void foo()
    {   std::cout << "Derived::foo()" << '\n';
    }
};

void DemoVirtual()
{
    BaseC<NotVirtual>* p1 = new Derived<NotVirtual>;
    p1->foo();  // calls Base::foo()

    BaseC<Virtual>* p2 = new Derived<Virtual>;
    p2->foo();  // calls Derived::foo()
}

// From foldtraverse.cpp
// #include "../tmpl/foldtraverse.hpp"

// traverse tree, using fold expression:
template<typename T, typename ... TP>
static Node* traversex (T np, TP ... paths)
{
    return (np ->* ... ->* paths);      // np ->* paths1 ->* paths2 ->* paths3 ...
}

void DemoFoldTraverse()
{
    // init binary tree structure:
    Node* root = new Node{5};
    root->subLeft = new Node{2};
    root->subLeft->subRight = new Node{4};
    root->subLeft->subRight->subLeft = new Node{3};
    root->subLeft->subLeft = new Node{1};
    root->subRight = new Node{10};
    root->subRight->subRight = new Node{20};
    root->subRight->subLeft = new Node{8};
    root->subRight->subLeft->subRight = new Node{9};

    // traverse binary tree:
    Node* node = Node::traverse(root, Node::right, Node::left, Node::right);
    cout << node->getValue() << '\n';
    node = root ->* Node::right ->* Node::left ->* Node::right;
    cout << node->getValue() << '\n';
    node = root -> subRight -> subLeft -> subRight;
    cout << node->getValue() << '\n';

    node = ::traversex(root, Node::left, Node::right, Node::left);
    cout << node->getValue() << '\n';
    node = root ->* Node::left ->* Node::right ->* Node::left;
    cout << node->getValue() << '\n';
    node = root -> subLeft -> subRight -> subLeft;
    cout << node->getValue() << '\n';
}

template<auto Sep = ' ', typename First, typename... Args>
void printauto1(const First& first, const Args&... args)
{
    cout << first;
    auto outWithSep = [](const auto& arg) { cout << Sep << arg;  };
    (... , outWithSep(args));
    cout << '\n';
}

template<typename T>
auto outWithSep2(string Sep, const T& arg)
{ cout << Sep << arg;  }

template<typename First, typename... Args>
void printauto2(string sep, const First& first, const Args&... args)
{
    cout << first;       // ::outWithSep2<Sep>(first);
    (... , ::outWithSep2(sep, args) );
    cout << '\n';
}

// From printauto.hpp
void DemoPrintAuto()
{
    printauto1("Hola1", "que", "tal!", "tengo", 47, "años", 'x', 35.67);
    printauto2(" ", "Hola2", "que", "tal!", "tengo", 47, "años", 'x', 35.67);
    printauto2("-", "Hola3", "que", "tal!", "tengo", 47, "años", 'x', 35.67);
    const string sep("-");
    printauto2(" - ", "Hola4", "que", "tal!", "tengo", 47, "años", 'x', 35.67);
}

void DemoLambdaFunctions()
{
    int  x = 4;
    auto y = [&r = x, x = x + 1]()->int
    {
        cout << "r=" << r << "  x=" << x << "(" << &x << ")" << endl;
        r += 2;
        // x += 10;  // error: cannot assign to a variable 
                     // captured by copy in a non-mutable lambda
        return x * x;
    }(); // updates ::x to 6 and initializes y to 25.
    cout << "y=" << y << " x=" << x << "(" << &x << ")" << endl;
}

// From: #include "../cppstd17/tmpl/vartmplauto.hpp"
template<typename T, auto N>
array<T,N> arr{};

template <typename Vect>
void printArr(Vect &v)
{
    for (const auto& elem : v)
    {  cout << elem << ' ';  }
    cout << endl;
}

void DemoVarTmplAuto()
{
    arr<int,5>[0]  = 17;
    arr<int,5>[3]  = 42;
    arr<int,5u>[1] = 11;
    arr<int,5u>[3] = 33;
    arr<int,10>[7] = 57;
    arr<int,15ll>[2] = 2; arr<int,15ll>[5] = 5;
    arr<float,10>[3] = 25;
    arr<long long,5>[3] = 14;
    //arr<double,5>[3] = 14;
    //arr<int,"Hola">[4] = 13;
    //arr<int,"Hola">[6] = 10;
    //arr<int,-6>[4] = 13;
    //arr<int,-6>[6] = 10;
    
    cout << "arr<int,5>   : ";    printArr(arr<int,5>);
    cout << "arr<int,5u>  : ";    printArr(arr<int,5u>);
    cout << "arr<int,10>  : ";    printArr(arr<int,10>);
    cout << "arr<float,10>: ";    printArr(arr<float,10>);
    cout << "arr<int,15ll>: ";    printArr(arr<int,15ll>);
    cout << "arr<long long,5>: ";    printArr(arr<long long,5>);
}

// From classarglambda.hpp
// #include <utility>     // for forward()
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
      return callback(forward<Args>(args)...);
    }
    auto count() const {  return calls; }
};

void DemoCallBacks()
{
    vector<int> vals{0, 8, 15, 42, 13, -1, 0};
    CountCalls cb(print);
    cb(vals);
    cb(vals);
    cout << "CountCalls=" << cb.count() << endl;
}

// From tmpl/ifcomptime.cpp

template< class T >
struct is_scalarx : integral_constant<bool,
                     is_arithmetic<T>::value     ||
                     is_enum<T>::value           ||
                     is_pointer<T>::value        ||
                     is_member_pointer<T>::value ||
                     is_null_pointer<T>::value> {};
                     
//class A {};

template <typename T>
string asString(T x)
{
    if constexpr(is_same_v<T, string>)
      return x;                  // statement invalid if no conversion to string
    else if constexpr(is_arithmetic_v<T>)
      return to_string(x);  // statement invalid if x is not numeric
    else
      return string(x);     // statement invalid if no conversion to string
}

class AA {};
void DemoIfCompTime()
{
    cout << asString(42) << '\n';
    cout << asString(string("hello")) << '\n';
    cout << asString("hello") << '\n';
    cout << asString(25.74) << "\n\n";

    cout << "is_arithmetic_v:\n"; // false
    cout << boolalpha
        << "A:           " << is_arithmetic_v<AA>           << '\n' // false
        << "bool:        " << is_arithmetic_v<bool>        << '\n' // true
        << "int:         " << is_arithmetic_v<int>         << '\n' // true
        << "int const:   " << is_arithmetic_v<int const>   << '\n' // true
        << "int &:       " << is_arithmetic_v<int&>        << '\n' // false
        << "int *:       " << is_arithmetic_v<int*>        << '\n' // false
        << "float:       " << is_arithmetic_v<float>       << '\n' // true
        << "float const: " << is_arithmetic_v<float const> << '\n' // true
        << "float &:     " << is_arithmetic_v<float&>      << '\n' // false
        << "float *:     " << is_arithmetic_v<float*>      << '\n' // false
        << "char:        " << is_arithmetic_v<char>        << '\n' // true
        << "char const:  " << is_arithmetic_v<char const>  << '\n' // true
        << "char &:      " << is_arithmetic_v<char&>       << '\n' // false
        << "char *:      " << is_arithmetic_v<char*>       << '\n' // false
        ;

    class cls { public: int m1, m2; };
      cout << (is_scalarx<int>::value ? "int is a scalar" : "int is not a scalar") << '\n';
      cout << (is_scalarx<cls>::value ? "cls is a scalar" : "cls is not a scalar") << '\n';
    cls obj;
      cout << (is_object_v<cls> ? "cls is an object" : "cls is not an object") << '\n';
      cout << (is_object_v<decltype(obj)> ? "obj is an object" : "obj is not an object") << '\n';
    int x = 5;
      cout << (is_object<decltype(x)>::value ? "x is an object" : "x is not an object") << '\n';

    auto pm = &cls::m1;
    cout << (is_member_object_pointer<decltype(pm)>::value ? "pm is a member function" : "pm is not a member function") << '\n';
    cout << (is_member_object_pointer_v<int> ? "int is a member function" : "int is not a member function") << '\n';
    cout << (is_member_object_pointer_v<int cls::*> ? "int cls::* is a member function" : "int cls::* is not a member function") << '\n';
    auto &ref = x;
    cout << (is_reference<decltype(ref)>::value ? "ref is a reference" : "ref is not a reference") << '\n';
    cout << (is_reference<decltype( x )>::value ? "x is a reference" : "x is not a reference") << '\n';
}

// From filesystem/checkpath3.cpp
#include <filesystem>
#include <cstdlib>    // for EXIT_FAILURE

void _DemoCheckPath3(string file)
{
    /*if (argc < 2)
    { cout << "Usage: " << argv[0] << " <path> \n";
      return EXIT_FAILURE;
    }*/
    namespace fs = std::filesystem;  
    //switch (fs::path p{argv[1]}; status(p).type())
    switch (fs::path p{file}; status(p).type())
    {
        case fs::file_type::not_found:
          cout << "\"" << setw(15) << p.string() << "\" does not exist\n";
          break;
        case fs::file_type::regular:
          cout << '"' << setw(15) << p.string() << "\" exists with "
                << file_size(p) << " bytes\n";
          break;
        case fs::file_type::directory:
          cout << '"' << setw(15) << p.string() << "\" is a directory containing:\n";
          for (const auto& e : filesystem::directory_iterator{p})
          {     if( status(p).type() == fs::file_type::directory )
                  cout << "\t" << e.path().string() << " is a directory\n";
                else if(status(p).type() == fs::file_type::regular) 
                    cout << "\t" << e.path().string() << file_size(e) << '\n'; 
          }
          break;
        default:
          cout << '"' << p.string() << "\" is a special file\n";
          break;
    }
}

void DemoCheckPath3()
{
    vector<string> files{"./iterator.h", "./main.o", "./abc.tex", "../../DSTuples"};
    for(auto f: files)
      _DemoCheckPath3(f);
}

// From filesystem/createfiles.cpp
//#include <iostream>
//#include <fstream>
//#include <filesystem>
//#include <cstdlib>    // for exit() and EXIT_FAILURE
void DemoCreateFile()
{
    namespace fs = std::filesystem;
    try
    { // create directories tmp/test/ (if they don't exist yet):
      fs::path testDir{"tmp/test"};
      create_directories(testDir);
      
      // create data file tmp/test/data.txt:
      auto testFile = testDir / "data.txt";
      ofstream dataFile{testFile};
      if (!dataFile)
      { cerr << "OOPS, can't open \"" << testFile.string() << "\"\n";
        exit(EXIT_FAILURE);  // exit program with failure
      }
      dataFile << "The answer is 42\n";

      // create symbolic link from tmp/slink/ to tmp/test/:
      create_directory_symlink("test", testDir.parent_path() / "slink");
    } 
    catch (const fs::filesystem_error& e)
    { cerr << "EXCEPTION: " << e.what() << '\n';
      cerr << "    path1: \"" << e.path1().string() << "\"\n";
    }

    // recursively list all files (also following symlinks)
    cout << fs::current_path().string() << ":\n";
    auto iterOpts{fs::directory_options::follow_directory_symlink};
    for (const auto& e : fs::recursive_directory_iterator(".", iterOpts))
    { cout << "  " << e.path().lexically_normal().string() << '\n'; 
    }
}

//#include <chrono>
//#include <filesystem>
#include <ctime>

/*string asString(const filesystem::file_time_type& ft)
{
    namespace fs = std::filesystem;
     std::time_t cftime = std::chrono::system_clock::to_time_t(
            std::chrono::file_clock::to_sys(ftime) );
    // convert to calendar time (including skipping trailing newline):
    string ts = ""; //ctime(ft);
    ts.resize(ts.size()-1);
    return ts;
}*/

/*#pragma clang diagnostic ignored "-Wswitch"
void DemoTimeAsString()
{
    namespace fs = std::filesystem;
    vector<string> files{"./iterator.h", "./main.o", "./abc.tex", "../../DSTuples"};
    
    for(auto file: files)
    {
        cout << "File: " << setw(15) << file << "    ";
        fs::path p{file};
        if( !exists(p) )
          cout << "does not exist" << endl;
        else if( is_regular_file(p) )
        {
            using namespace std::chrono_literals;
            fs::file_time_type ftime = std::filesystem::last_write_time(file);
            std::time_t cftime = std::chrono::system_clock::to_time_t(
                                    std::chrono::file_clock::to_sys(ftime));
            //std::cout << "File write time is " << std::asctime(std::localtime(&cftime));
            //auto ftime = std::filesystem::file_time_type(file);
            //cout << string(ftime) << endl;
        }
        //auto type = status(p).type();
    }
}
*/

// From: filesystem/syslink.hpp 
void testSymLink(std::filesystem::path top)
{
    top = absolute(top);      // use absolute paths as we change current path
    create_directory(top);    // make sure top exists
    current_path(top);        // so that we can change the directory to it
    std::cout << std::filesystem::current_path() << '\n'; // print path of top

    remove_all(std::filesystem::path("a"));

    // define our sub-directories (without creating them):
    std::filesystem::path px{top / "a/x"};
    std::filesystem::path py{top / "a/y"};
    std::filesystem::path ps{top / "a/s"};

    // print some relative paths (for non-existing files):
    std::cout << "relative path from top: " << px.relative_path() << '\n';        // relative path from top
    std::cout << "to px from py         : " << px.lexically_relative(py) << '\n'; // to px from py: "../x"
    std::cout << "relative(px from, py) : " << relative(px, py) << '\n';          // to px from py: "../x"
    std::cout << "to px from curr. path : " << relative(px) << '\n';              // to px from curr. path: "a/x"

    std::cout << "to px from ps         : " << px.lexically_relative(ps) << '\n'; // to px from ps: "../x"
    std::cout << "relative(px from ps)  : " << relative(px, ps) << '\n';          // to px from ps: "../x"

    // now create all sub-directories and the symbolic link:
    create_directories(px);                         // create "top/a/x"
    create_directories(py);                         // create "top/a/y"
    /*
    if (!is_symlink(ps))
      create_directory_symlink(top, ps);            // create "top/a/s" -> "top" 
    std::cout << "ps                    : " << ps << " -> " << read_symlink(ps) << '\n';
    // and see the difference between lexically and filesystem relative:
    std::cout << "px from ps            : " << px.lexically_relative(ps) << '\n'; // to px from ps: "../x"
    std::cout << "px from ps            : " << relative(px, ps) << '\n';          // to px from ps: "a/x"
    */
    remove_all(std::filesystem::path("a"));
}

void DemoSymlink()
{
    std::filesystem::path p{"."};
    testSymLink(p);
}

//#include <optional>
//#include <string_view>
//#include <charconv>     // for from_chars()
// From lib/asint.cpp
// convert string to int if possible:

template <typename T>
std::optional<T> convert(std::string_view sv, T &val)
{
    // read character sequence into the int:
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data()+sv.size(), val);
    // if we have an error code, return no value:
    if (ec != std::errc{})
      return std::nullopt;
    return val;
}

void DemoConvert()
{  
    for (auto s : {"42", "  077", "hello", "0x33", "-532", "035"} )
    {
        // try to convert s to int and print the result if possible:
        int val;
        std::optional<decltype(val)> oi = convert(s, val);
        if (oi)
          std::cout << "convert '" << s << "' to int: " << *oi << "\n";
        else
          std::cout << "can't convert '" << s << "' to int\n";
    }
}

// From "../../cppstd17/lib/incomplete.cpp"
#include "../../cppstd17/lib/incomplete.hpp"
void DemoIncomplete()
{
    // create node tree:
    NodeIncomplete root("top");
    root.add(   NodeIncomplete("Jose"));
    root.add(   NodeIncomplete("Maria"));
    root[0].add(NodeIncomplete("Jesus"));
    root[1].add(NodeIncomplete("Roxana"));
    root[1].add(NodeIncomplete("Ana"));
    // print NodeIncomplete tree:
    root.print();
}

// From "../../cppstd17/lib/nodehandle.cpp"

template<typename T>
void printMap(const T& coll1)
{
    for (const auto& [key, value] : coll1)
      std::cout << "  [" << key << ":" << value << "]";
    std::cout << '\n';
}

template<typename ... T>
void printMaps(const T& ... maps)
{
    std::cout << "values:\n";
    (..., printMap(maps));
}

// From ../../cppstd17/lib/nodemerge.cpp
// #include <map>
void DemoMapHandle()
{
    std::map<int, std::string> m{{1, "mango"},
                                {2, "papaya"},
                                {3, "guava"}};

    auto nh = m.extract(2);  // nh has type decltype(m)::node_type
    nh.key() = 4; 
    m.insert(std::move(nh));
    for (const auto& [key, value] : m)
        std::cout << key << ": " << value << '\n';
}

void DemoMapNodeMerge()
{
    std::multimap<double, std::string> src {{1.1, "one"},
                                            {2.2, "two"},
                                            {3.3, "three"}}; 
    std::map<double, std::string> dst {{3.3, "old data"}}; 
    printMaps(src, dst);

    // merge all elements from src into dst:
    dst.merge(src);
    printMaps(src, dst);
}

void DemoMapNodeMove()
{
    std::multimap<double, std::string> src {{1.1, "one"},
                                            {2.2, "two"},
                                            {3.3, "three"}}; 
    std::map     <double, std::string> dst  {{3.3, "old data"}}; 
    printMaps(src, dst);

    // move some elements from multimap src to map dst:
    dst.insert(src.extract(src.find(1.1)));  // splice using an iterator 
    dst.insert(src.extract(2.2));            // splice using the key
    printMaps(src, dst);
}

// From ../../cppstd17/lib/varioantpoly1.cpp
#include "../../cppstd17/lib/coord.hpp"
#include "../../cppstd17/lib/line.hpp"
#include "../../cppstd17/lib/circle.hpp"
#include "../../cppstd17/lib/rectangle.hpp"

using GeoObj = std::variant<Line, Circle, Rectangle>;
// create and initialize a collection of geometric objects:
std::vector<GeoObj> createFigure()
{
    std::vector<GeoObj> f;
    f.push_back(Line{Coord{1,2},Coord{3,4}});
    f.push_back(Circle{Coord{5,5},2});  
    f.push_back(Rectangle{Coord{3,3},Coord{6,4}});  
    return f;
}

void DemoVariantPoly1()
{
    std::vector<GeoObj> figure = createFigure();
    for (const GeoObj& geoobj : figure)
    {
        std::visit([] (const auto& obj) 
        { obj.draw();  // polymorphic call of draw()
        },
        geoobj);
    }
}

void DemoVariantPoly2()
{
    using Var = std::variant<int, double, std::string>;
    std::vector<Var> values {42, 0.19, "hello world", 0.815, "Hi!"};
    for (const Var& val : values)
    {
        std::visit([] (const auto& v)
        {
            if constexpr(std::is_same_v<decltype(v), const std::string&>)
                std::cout << '"' << v << "\" ";
            else
                std::cout << v << ' ';
        },
        val);
    }
    std::cout << std::endl;
}

//#include "../../cppstd17/tmpl/overload.hpp"

// "inherit" all function call operators of passed base types:qa
template<typename ... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};

// base types are deduced from passed arguments (not needed as of C++20)
template<typename ... Ts>
overload(Ts...) -> overload<Ts...>;

void DemoVariantPoly3()
{
    using Var = std::variant<int, double, std::string>;
    std::vector<Var> values {42, 0.19, "hello world", 0.815};
    for (const auto& val : values)
    {
      std::visit(overload{
                  [] (auto v) {  std::cout << v << ' ';  },
                  [] (const std::string& v) {  std::cout << '"' << v << "\" "; }
                },
                val);
    }
    std::cout << std::endl;

    using namespace std;
    vector<variant<int, string, double>> vals {42, "hi", 8, 7.14};
    for (const auto& v : vals)
    {
        std::visit( overload {
                  [] (auto i) { cout << "auto(" << i << ") "; },
                  [] (double i) { cout << "double(" << i << ")" << ' '; },
                  [] (const string& s) { cout << '"' << s << "\" "; }
                },
                v);
    } 
    std::cout << std::endl;
}

// slightly modified From: https://en.cppreference.com/w/cpp/utility/variant/visit
// helper constant for the visitor #3
template<class> inline constexpr bool always_false_v = false;

void DemoVariantPoly4()
{
    // the variant to visit
    using Var = std::variant<int, long, long long, double, std::string>;
    std::vector<Var> vec = {10, 15l, 1.5, 30LL, "hello"};
    for(auto& v: vec)
    {
        // 1. void visitor, only called for side-effects (here, for I/O)
        std::visit([](auto&& arg){std::cout << "#1 " << std::setw(7) << arg;}, v);
        // 2. value-returning visitor, demonstrates 
        // the idiom of returning another variant
        Var w = std::visit([](auto&& arg) -> Var {return arg + arg + arg;}, v);
 
        // 3. type-matching visitor: a lambda that handles each type differently
        std::cout << ". x3, var holds ";
        std::visit([](auto&& arg)
        {
            using T = std::decay_t<decltype(arg)>;
            //string type_txt = type_name<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                std::cout << "int       : " << arg << "\n";
            else if constexpr (std::is_same_v<T, long>)
                std::cout << "long      : " << arg << "\n";
            else if constexpr (std::is_same_v<T, long long>)
                std::cout << "long long : " << arg << "\n";
            else if constexpr (std::is_same_v<T, double>)
                std::cout << "double    : " << arg << "\n";
            else if constexpr (std::is_same_v<T, std::string>)
                std::cout << "string    : " << std::quoted(arg) << "\n";
            else 
                static_assert(always_false_v<T>, "non-exhaustive visitor!");
            //std::cout << "int       : " << arg << "\n";
        }, w);
    }
 
    std::cout << "\nSecond part\n";
    for (auto& v: vec) 
    {
        // 4. another type-matching visitor: a class with 3 overloaded operator()'s
        // Note: The `(auto arg)` template operator() will bind to `int` and `long`
        //       in this case, but in its absence the `(double arg)` operator()
        //       *will also* bind to `int` and `long` because both are implicitly
        //       convertible to double. When using this form, care has to be taken
        //       that implicit conversions are handled correctly.
        auto visitor = overload {
            [](auto arg)               { std::cout << "auto(" << arg << ") "; },
            [](long long arg)          { std::cout << "long long(" << arg << ") "; },
            [](double arg)             { std::cout << "double(" << std::fixed << arg << ") "; },
            [](const std::string& arg) { std::cout << "string(" << std::quoted(arg) << ") "; }
        };
        std::visit(visitor, v);
    }
    std::cout << std::endl;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
 
std::mutex m;
struct X
{
    void foo(int i, const std::string& str)
    {   std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }
    void bar(const std::string& str)
    {   std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }
    int operator()(int i)
    {   std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};
 
template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);
 
    RandomIt mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
 
void DemoMutex()
{
    std::vector<int> v(1000000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
 
    X x;
    // Calls (&x)->foo(42, "Hello") with default policy:
    // may print "Hello 42" concurrently or defer execution
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // Calls x.bar("world!") with deferred policy
    // prints "world!" when a2.get() or a2.wait() is called
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // Calls X()(43); with async policy
    // prints "43" concurrently
    auto a3 = std::async(std::launch::async, X(), 43);
    a2.wait();                     // prints "world!"
    std::cout << a3.get() << '\n'; // prints "53"
} // if a1 is not done at this point, destructor of a1 prints "Hello 42" here


// From tmplbook/names/anglebrackethack.cpp

#include <iostream>

template<int I>
struct XA
{  static int const c = 15;
};

template<> 
struct XA<0>
{  typedef int c;
};

template<typename T>
struct YA
{  static int const c = 20;
};
static int const c = 2;

void DemoAngleBracketHack()
{
    std::cout << (YA<XA<1> >::c ) << endl;
    std::cout << (YA<XA<1> >::c >= ::c) << endl;
    std::cout << (YA<XA<1> >::c >= ::c >= ::c) << endl;
}

// From: https://en.cppreference.com/w/cpp/utility/forward
// * If a call to wrapper() passes an rvalue std::string, 
//   then T is deduced to std::string (not std::string&, const std::string&, or std::string&&), 
//   and std::forward ensures that an rvalue reference is passed to foo.
// * If a call to wrapper() passes a const lvalue std::string, 
//   then T is deduced to const std::string&, and std::forward ensures that 
//   a const lvalue reference is passed to foo.
// * If a call to wrapper() passes a non-const lvalue std::string, 
//   then T is deduced to std::string&, and std::forward ensures that 
//   a non-const lvalue reference is passed to foo.

#include <iostream>
#include <memory>
#include <utility>

struct AR
{
    AR(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
    AR(int& n)  { std::cout << "lvalue overload, n=" << n << "\n"; }
};
 
class BR
{
public:
    template<class T1, class T2, class T3>
    BR(T1&& t1, T2&& t2, T3&& t3) :
        a1_{std::forward<T1>(t1)},
        a2_{std::forward<T2>(t2)},
        a3_{std::forward<T3>(t3)}
    {
    }
private:
    AR a1_, a2_, a3_;
};
 
template<class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{   return std::unique_ptr<T>(new T(std::forward<U>(u)));
}
 
template<class T, class... U>
std::unique_ptr<T> make_unique2(U&&... u)
{   return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}
 
void DemoMakeUnique()
{   
    auto p1 = make_unique1<AR>(2); // rvalue
    int i = 1;
    auto p2 = make_unique1<AR>(i); // lvalue
 
    std::cout << "BR\n";
    auto t = make_unique2<BR>(2, i, 3);
}

class A {};
class B : A {};
class C {};
 
void DemoIsBaseOf() 
{
    cout << boolalpha;
    cout << "a2b: " << is_base_of_v<A, B> << '\n';
    cout << "b2a: " << is_base_of_v<B, A> << '\n';
    cout << "c2b: " << is_base_of<C, B>::value << '\n';
    cout << "same type: " << is_base_of<C, C>::value << '\n';
}

template <typename Base>
struct MyTrait
{
    static constexpr bool value = false;
    //void flip() {value = !value; }
};
template <>
struct MyTrait<A>
{
    static constexpr bool value = true;
    //void flip() {value = !value; }
};

template <typename Base>
inline constexpr bool MyTrait_v = MyTrait<Base>::value;
void DemoTraits()
{
    if( MyTrait<int>::value )
        cout << boolalpha << "MyTrait<int>::value = " << true << endl;
    else
       cout << boolalpha << "MyTrait<int>::value = " << false << endl;

    if( MyTrait_v<A> )
        cout << boolalpha << "MyTrait_v<A> = " << true << endl;
    else
       cout << boolalpha << "MyTrait_v<A> = " << false << endl;
}

// From tmplbook/basics/arrays.cpp and arrays.hpp
template<typename T>
struct MyClass;             // primary template

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>       // partial specialization for arrays of known bounds
{
  static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]>    // partial spec. for references to arrays of known bounds
{
    static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template<typename T>
struct MyClass<T[]>         // partial specialization for arrays of unknown bounds
{
    static void print() { std::cout << "print() for T[]\n"; }
};

template<typename T>
struct MyClass<T(&)[]>      // partial spec. for references to arrays of unknown bounds
{
    static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
struct MyClass<T*>          // partial specialization for pointers
{
    static void print() { std::cout << "print() for T*\n"; }
};

template<typename T1, typename T2, typename T3>
void TestingParamsTypes(int a1[7], int a2[],    // pointers by language rules
         int (&a3)[42],          // reference to array of known bound
         int (&x0)[],            // reference to array of unknown bound
         T1 x1,                  // passing by value decays
         T2& x2, T3&& x3)        // passing by reference
{
    MyClass<decltype(a1)>::print();     // uses MyClass<T*>
    cout << "Type for a1: " << type_name<decltype(a1)>() << "\n\n";
    MyClass<decltype(a2)>::print();     // uses MyClass<T*>
    cout << "Type for a2: " << type_name<decltype(a2)>() << "\n\n";
    MyClass<decltype(a3)>::print();     // uses MyClass<T(\&)[SZ]>
    cout << "Type for a3: " << type_name<decltype(a3)>() << "\n\n";
    MyClass<decltype(x0)>::print();     // uses MyClass<T(\&)[]>
    cout << "Type for x0: " << type_name<decltype(x0)>() << "\n\n";
    MyClass<decltype(x1)>::print();     // uses MyClass<T*>
    cout << "Type for x1: " << type_name<decltype(x1)>() << "\n\n";
    MyClass<decltype(x2)>::print();     // uses MyClass<T(\&)[]>
    cout << "Type for x2: " << type_name<decltype(x2)>() << "\n\n";
    MyClass<decltype(x3)>::print();     // uses MyClass<T(\&)[]>
    cout << "Type for x3: " << type_name<decltype(x3)>() << "\n\n";
}

// From tmplbook/basics/cref.cpp
#include <functional>  // for std::cref()
#include <string>
#include <iostream>

void printString(std::string const& s)
{
    std::cout << s << '\n';
}

template<typename T>
void printT(T arg)
{
    printString(arg);        // might convert arg back to std::string
    cout << "Type for arg: " << type_name<decltype(arg)>() << "\n\n";
}

void DemoTestArray()
{
    int a[42];
    MyClass<decltype(a)>::print();        // uses MyClass<T[SZ]>

    extern int ExtArray[];                // forward declare array
    MyClass<decltype(ExtArray)>::print(); // uses MyClass<T[]>

    TestingParamsTypes(a, a, a, ExtArray, ExtArray, ExtArray, ExtArray);

    std::string s = "Text by reference and value";
    printT(s);               // print s passed by value
    printT(std::cref(s));    // print s passed ``as if by reference''
}

int ExtArray[] = {0, 8, 15};            // define forward-declared array

template<typename T>
void tmplParamIsReference(T)
{   std::cout << "T is reference: " << std::is_reference_v<T> << '\n';
}

void DemoTemplateParamTypes()
{
    std::cout << std::boolalpha;
    int i;
    int& r = i;
    tmplParamIsReference(i);         // false
    tmplParamIsReference(r);         // false
    tmplParamIsReference<int&>(i);   // true
    tmplParamIsReference<int&>(r);   // true
}

#include <string>
#include <map>
#include <algorithm>

const int nElem = 20;
TX vect[nElem] = {30, 5, 14, 7,80, 90, 37, 25, 54, 47, 3, 6, 12, 8, 25, 27, 19, 83, 9, 17};

template <typename T>
void print_bs(T &bs)
{
    cout << bs << endl;
}

// From tmplbook/basics/foreach.cpp
template<typename Iter, typename Callable>
void foreach (Iter current, Iter end, Callable op)
{
    while (current != end)    // as long as not reached the end
    { op(*current);           //  call passed operator for current element
      ++current;              //  and move iterator to next element
    }
}

// a function to call:
void func(int i)
{
    std::cout << "func() called for: " << i << '\n';
}

// a function object type (for objects that can be used as functions):
class FuncObj
{ public:
    void operator() (int i) const  // Note: const member function
    {  std::cout << "FuncObj::op() called for: " << i << '\n';
    }
};

void DemoForeach()
{
    std::vector<int> primes = {2, 3};
    foreach(primes.begin(), primes.end(), func);      // function as callable (decays to pointer)
    foreach(primes.begin(), primes.end(),  &func);    // function pointer as callable
    foreach(primes.begin(), primes.end(), FuncObj()); // function object as callable
    foreach(primes.begin(), primes.end(),  
            [] (int i) {  std::cout << "lambda called for: " << i << '\n';  });
}

// From tmplbook/basics/foreachinvoke.cpp

#include <iostream>
#include <vector>
#include <string>
//#include "foreachinvoke.hpp"

template<typename Iter, typename Callable, typename... Args>
void foreach (Iter current, Iter end, Callable op, Args const&... args)
{
    while (current != end)     // as long as not reached the end of the elements
    {   std:invoke(op,  args..., *current);
        ++current;
    }
}

// a class with a member function that shall be called
class MyClassInvoke
{public:
    void memfunc(string str, int i) const
    { std::cout << "MyClass::memfunc() called for: " << i << " and str: " << str << '\n';  }
};

void DemoForeachInvoke()
{
    std::vector<int> primes = {2, 3};
    // pass lambda as callable and an additional argument:
    foreach(primes.begin(), primes.end(),        // elements for 2nd arg of lambda
            [](std::string const& prefix, int i) // lambda to call
            { std::cout << prefix << i << '\n';
            }, 
            "- value: ");                        // 1st arg of lambda

    // call obj.memfunc() for/with each elements in primes passed as argument
    MyClassInvoke obj;
    foreach(primes.begin(), primes.end(),  // elements used as args
            &MyClassInvoke::memfunc,       // member function to call
            obj, "extra");                 // object to call memfunc() for

    foreach(primes.begin(), primes.end(),  // elements used as args
            &decltype(obj)::memfunc,       // member function to call
            obj, "New extra");             // object to call memfunc() for
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

void DemoInvoke()
{
    vector<int> vals{0, 8, 15, 42, 13, -1, 0};
    call([&vals]() -> void
    {  cout << "size: " << vals.size() << '\n';
    });
    call([&vals](int a)
    {  cout << "size: " << vals.size() << ", a=" << a << '\n';
    }, 5);
    print(vals);
    auto w0 = call(print, vals);
    cout << "w0=" << w0 << endl;

    call(&decltype(vals)::pop_back, vals);    // vals.pop_back();
    auto w1 = call(print, vals);
    cout << "w1=" << w1 << endl;

    call(&decltype(vals)::clear, vals);       // vals.clear();
    auto w2 = call(print, vals);
    cout << "w2=" << w2 << endl;

    cout << "Type of vals: " << type_name<decltype(vals)>() << endl;
    cout << "Type of w2: " << type_name<decltype(w2)>() << endl;

    auto pf = &print;
    cout << "Type of pf: " << type_name<decltype(pf)>() << endl;
}

template<typename T, unsigned N>
std::size_t len (T(&)[N]) 
{ 
    return N;
}

// number of elements for a type having size_type:
template<typename T>
typename T::size_type len (T const& t) 
{   return t.size();
}

// fallback for all other types:
std::size_t len (...)
{   return 0;
}

void DemoLen()
{
    vector<int> v1{0, 8, 15, 42, 13, -1, 0};
    int v2[] = {0, 8, 15, 42, 13, -1, 0, 5, 7};
    int v3[] = {0, 8, 15, 42, 13, -1, 0, 5, 7, 8, 10, 12};
    double v4 = 7.2;

    cout << "v1 -> " << len(v1) << " elements\n";
    cout << "v2 -> " << len(v2) << " elements\n";
    cout << "v3 -> " << len(v3) << " elements\n";
    cout << "v4 -> " << len(v4) << " elements\n";
}

// From tmpl/basics/max3val.cpp
#include <cstring>
#include <string>

// maximum of two values of any type:
template<typename T>
T Max (T a, T b)
{   return  b < a ? a : b;
}

// maximum of two pointers:
template<typename T>
T* Max (T* a, T* b)
{  return  *b < *a  ? a : b;    }

// maximum of two C-strings:
char const* Max (char const* a, char const* b)
{   return  std::strcmp(b,a) < 0  ? a : b;    }

template<typename T, typename ... Q>
auto Max(const T&a, const T&b, const Q& ... args)
{    return Max(Max(a, b), args...);        }

void DemoMax()
{
    int a = 7, b = 42, c = 35, d = 18;
    auto m1 = Max(a,b);     // Max() for two values of type int
    cout << "Max(7,42)= " << m1 << endl;
    m1 = Max(a,b,c,d);
    cout << "Max(7,42,35,18)= " << m1 << endl;

    std::string s1 = "hey", s2 = "you", s3 = "zuzu";
    auto m2 = ::Max(s1,s2);   
    cout << "Max(hey,you)= " << m2 << endl;
    m2 = ::Max(s1,s2,s3);   
    cout << "Max(hey,zuzu,you)= " << m2 << endl;

    int* p1 = &b, *p2 = &a, *p3 = &c, *p4 = &d;
    auto m3 = ::Max(p1,p2);   // Max() for two pointers
    cout << "Max(p1,p2)= " << *m3 << endl;
    m3 = ::Max(p1,p2,p3,p4);   // Max() for two pointers
    cout << "Max(p1,p2,p3,p4)= " << *m3 << endl;

    char const* x = "hello", *y = "world", *z = "bye";
    auto m4 = ::Max(x,y);     // Max() for two C-strings
    cout << "Max(hello,world)= " << m4 << endl;
    m4 = ::Max(x,y,z);     // Max() for two C-strings
    cout << "Max(hello,world,bye)= " << m4 << endl;
}

class CK
{
  public:
    CK() = default;
    CK (CK const&)
    { std::cout << "copy constructor\n";    }
    CK (CK&&)
    { std::cout << "move constructor\n";    }
    
    template<typename T>
    CK (T&&)
    { std::cout << "template constructor\n";}
};

// tmplbook/details/tmplconstr.cpp
// ! Pending Er to understand \/
void DemoConstructor() 
{
    CK x;
    CK x2{x};             // prints: template constructor
    CK x3{std::move(x)};  // prints: move constructor
    CK const c;
    CK x4{c};             // prints: copy constructor
    CK x5{std::move(c)};  // prints: template constructor
}

// From tmplbook/details/inject.cpp
int CW;

class CW
{
  private:
    int i[5]; 
  public:
    static int f() {  return sizeof(CW);     }
};

int f() 
{ 
    return sizeof(CW); 
}

void DemoSizeScope() 
{
   std::cout << "CW::f() = " << CW::f() << ',' << '\n'
             << "::f() = " << ::f() << '\n'
             << sizeof(class CW) << '\n';
}


void DemoBitset()
{
    bitset<10> bs1;
    bitset<10> bs2(5);
    bitset<10> bs3("00010101");
    print_bs(bs1);
    print_bs(bs2);
    print_bs(bs3);
    //bs3.
}

template <typename LinkedList>
void demoLinkedList(LinkedList &mylist)
{
    cout << "Inserting:       ";
    for(auto x=0; x<nElem; x++)
    {   
      cout << vect[x] << ", "; 
      mylist.insert(vect[x]);
    }
    cout << endl;
    cout << "Lista en orden: ";
    recorrer(mylist, fx);  cout << endl;
}

void demoLinkedListSorted()
{
    cout << "Ascending list" << endl;
    LinkedList< LLTraitAsc<TX> > myAscList;
    demoLinkedList(myAscList);

    cout << "Descending list" << endl;
    LinkedList< LLTraitDesc<TX> > myDescList;
    demoLinkedList(myDescList);
}

template <typename DoubleList>
void demoDoubleLinkedList(DoubleList &mylist)
{
    cout << "Inserting:       ";
    for(auto x=0; x<nElem; x++)
    {   
      cout << vect[x] << ", "; 
      mylist.insert(vect[x]);
      //mylist.push_back(vect[x]);
    }
    cout << endl;
    cout << "Lista en orden : ";
    recorrer(mylist, fx);  cout << endl;
    
    cout << "Lista invertida: ";
    recorrer_inverso(mylist, fx);  cout << endl;
}

void demoDoubleLinkedListSorted()
{
    cout << "Ascending double list" << endl;
    DoubleLinkedList< DLLAscTraits<TX> > myAscList;
    demoDoubleLinkedList(myAscList);

    cout << "Descending double list" << endl;
    DoubleLinkedList< DLLDescTraits<TX> > myDescList;
    demoDoubleLinkedList(myDescList); 
}

void DemoDSMap()
{
    std::map<std::string, double> coll;
    coll["Ernesto"] = 47.6;
    // {"Gaby", 49.3}, 
    // {"Johannes", 37},    {"Paula", 15}}           
    std::string match = "Johannes";
    auto pos = std::find_if (coll.begin(), coll.end(), 
                            [&match](auto &s) {  return s.first != match;  } );
    cout << match << " ";
    if( pos != coll.end() )
        cout << "was found! :" << pos->second << endl;
    else
        cout << "was not found! " << endl;
}

// From tmplbook/basics/stack9.hpp
#include "stack9.hpp"
#include <iostream>
#include <vector>

void DemoStack()
{
    Stack<int>   iStack;     // stack of ints
    Stack<float> fStack;     // stack of floats

    // manipulate int stack
    iStack.push(1);
    iStack.push(2);
    std::cout << "iStack.top(): " << iStack.top() << '\n';

    // manipulate float stack:
    fStack.push(3.3);
    std::cout << "fStack.top(): " << fStack.top() << '\n';

    // assign stack of different type and manipulate again
    fStack = iStack;
    fStack.push(4.4);
    std::cout << "fStack.top(): " << fStack.top() << '\n';

    // stack for doubless using a vector as an internal container
    Stack<double, std::vector> vStack;
    vStack.push(5.5);
    vStack.push(6.6);
    std::cout << "vStack.top(): " << vStack.top() << '\n';

    vStack = fStack;
    std::cout << "vStack: ";
    while (! vStack.empty())
    {
        std::cout << vStack.top() << ' ';
        vStack.pop();
    }
    std::cout << '\n';
}

template <typename Container>
void print(Container &container)
{
    auto itr = container.begin();
    for (; itr != container.end(); itr++)
    {
        cout << *itr<<" ";
    }
    cout << endl;
}

// From DSMultiset
#include <set>
void DemoMultiset()
{ 
    vector<int> v {10, 20, 30, 40, 40, 50, 50, 50, 60, 60, 70, 70, 80, 90};
    multiset<int> MSet; // less<int> default 10 20 30 40 50 60 70 80 90
    multiset<int>::iterator one, end;
    MSet.insert(v.begin(), v.end());
    print(MSet);
    one = MSet.lower_bound (50); 
    end = MSet.upper_bound (80); // 50 <= x <= 80;
    MSet.erase(one , --end); // 10 20 30 40         90
    cout<<"Elements are: ";
    print(MSet);
    cout << '\n';
    v.clear();
    print(MSet);

    MSet.insert(v.begin(), v.end());
    // Removes 60, 70, 80
    //MSet.erase(MSet.find(60) , MSet.find(70)); // 60 <= x < 90
    print(MSet);

    multiset<int> alice{1, 2, 3};
    multiset<int> bob{7, 8, 9, 10};
    multiset<int> eve{1, 2, 3};
 
    cout << boolalpha;
 
    // Compare non equal containers
    cout << "alice == bob returns " << (alice == bob) << '\n';
    cout << "alice != bob returns " << (alice != bob) << '\n';
    cout << "alice <  bob returns " << (alice < bob) << '\n';
    cout << "alice <= bob returns " << (alice <= bob) << '\n';
    cout << "alice >  bob returns " << (alice > bob) << '\n';
    cout << "alice >= bob returns " << (alice >= bob) << '\n';
 
    cout << '\n';
 
    // Compare equal containers
    cout << "alice == eve returns " << (alice == eve) << '\n';
    cout << "alice != eve returns " << (alice != eve) << '\n';
    cout << "alice <  eve returns " << (alice < eve) << '\n';
    cout << "alice <= eve returns " << (alice <= eve) << '\n';
    cout << "alice >  eve returns " << (alice > eve) << '\n';
    cout << "alice >= eve returns " << (alice >= eve) << '\n';
    
    //cout << "alice <=> eve returns " << (alice <=> eve) << '\n';
    //cout << "alice <=> bob returns " << (alice <=> bob) << '\n';
}

bool myfunction (int i,int j)
{ return (i<j); }

class myclass
{public:
  bool operator() (int i,int j) { return (i<j);}
};

void DemoSort1()
{
    vector<int> v1 {70, 50,    80, 90, 60, 30, 10,    40, 50, 40, 60, 70, 20, 50};
    print(v1);
    vector<int> v2(v1), v3(v1), v4(v1), v5(v1), v6(v1), v7(v1);
    sort(v2.begin()+2, v2.begin()+7);
    print(v2);

    sort(v3.begin(), v3.end());
    print(v3);

    sort(v4.begin(), v4.end(), less<int>()); // less<int> by default
    print(v4);

    sort(v5.begin(), v5.end(), greater<int>());
    print(v5);

    sort(v6.begin(), v6.end(), [](int a, int b){return a<b;} );
    print(v6);

    sort(v7.begin(), v7.end(), myclass());
    print(v7);
}

bool compare(pair<int, int> a, pair<int, int> b)
{
    if( a.second != b.second )
      return a.second < b.second; // de menor a mayor por el segundo
    return a.first  > b.first;    // luego de > a < por el 1ro
}

void DemoSort2()
{
    pair<int, int> pairs[] = {{1, 2}, {2, 1}, {7, 1}, {5, 3}, {4,1}, {3, 1}};
    sort(pairs, pairs+6, compare);
    for(auto p:pairs)
        cout << p.first << ", " << p.second << endl;
    // print(pair)
}

void DemoPermutation()
{
    vector<int> v1 {70, 50, 80, 90, 60};
    // sort(v1.begin(), v1.end());
    print(v1);
    int x = 1;
    do
    {
        cout << setw(3) << left << x << ": "; 
        print(v1);
        x++;
    }//while(next_permutation(v1.begin(), v1.end()));
    while(prev_permutation(v1.begin(), v1.end()));
}
