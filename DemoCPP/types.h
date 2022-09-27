#ifndef __TYPES_H__
#define __TYPES_H__

#include <string.h>

using T1=double;
using TX=long;
using namespace std;

/*
template <typename _T>
struct Min {
  bool operator() (const _T& x, const _T& y) const {return strcmp(x,y) < 0;}
  typedef _T first_argument_type;
  typedef _T second_argument_type;
  typedef bool result_type;
};

template <typename _T>
struct Max {
  bool operator() (const _T& x, const _T& y) const {return strcmp(x,y) > 0;}
  typedef _T first_argument_type;
  typedef _T second_argument_type;
  typedef bool result_type;
};
*/

template <typename _T>
struct BTreeTraitAsc
{
    using  Type      = _T;
    using  ObjIDType    = long;
    using  CompareFn = less<Type>;
};

template <typename _T>
struct BTreeTraitDesc
{
    using  Type      = _T;
    using  ObjIDType    = long;
    using  CompareFn = greater<Type>;
};

#endif