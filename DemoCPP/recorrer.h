#ifndef __RECORRRER_H__  
#define __RECORRRER_H__ 
#include "object_function.h"
using namespace std;

void fx(TX &x)
{  cout << x << "  "; }

void inc(TX &x)
{  ++x; }

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
    recorrer(container, fx);  cout << endl; // recorre imprimiendo
    recorrer(container, inc);  // recorre incrementando
    recorrer(container, fx);  cout << endl; // recorre imprimiendo

    // funciones lambda
    recorrer(container, [](TX &n){ n-= 5;}); cout << endl; // -5 a todos
    recorrer(container, fx);  cout << endl; // recorre imprimiendo
    
    OperacionEspecial<TX> ope; 
    recorrer(container, ope);  
    recorrer(container, fx);  cout << endl;
}

#endif
