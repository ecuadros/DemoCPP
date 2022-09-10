#ifndef __RECORRRER_H__  
#define __RECORRRER_H__ 
#include "object_function.h"
using namespace std;

template <typename T>
void fx(T &x)   //funciona como un tipo
{  cout << x << "  "; }

template <typename T>
void inc(T &x)
{  ++x; }

template <typename T>
void inc2(T &x)
{  to_string(int(x) + 1).c_str(); }

template <typename T>
void inc3(T &x)
{  x; }

template <typename Iterator, typename F>
void recorrer(Iterator ItBegin, Iterator ItEnd, F ope)
{
  auto iter = ItBegin;
  for(; iter != ItEnd ; ++iter)
      ope(*iter);
}

// #1
template <typename Container, typename F>
void recorrer(Container &container, F ope)
{  
    recorrer(container.begin(), container.end(), ope);
}

// TODO implementar el recorrer inverso
// # 2
template <typename Container, typename F>
void recorrer_inverso(Container &container, F ope)
{ recorrer(container.rbegin(), container.rend(), ope);
}

template <typename Container>
void recorrer(Container &container)
{
    using T = typename Container::value_type;
    recorrer(container, fx<T>);  cout << endl; // recorre imprimiendo
    recorrer(container, inc<T>);  // recorre incrementando sin imprimir
    recorrer(container, fx<T>);  cout << endl; // recorre imprimiendo después de incremetarlo

    // funciones lambda
    recorrer(container, [](T &n){ n-= 5;}); cout << endl; // -5 a todos
    recorrer(container, fx<T>);  cout << endl; // recorre imprimiendo
    
    OperacionEspecial<T> ope; 
    recorrer(container, ope);  
    recorrer(container, fx<T>);  cout << endl; // recorre imprimiendo después de hacer la operación especial
}

#endif
