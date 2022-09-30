#ifndef __TYPES_H__
#define __TYPES_H__
#include <string.h>
using namespace std;

using T1=double;
using TX=long;

template <typename _T>
struct BTreeTraitDesc
{
    using  Type      = _T;
    using  ObjIDType    = long;
    using  CompareFn = greater<Type>;
};

template <typename _T>
struct BTreeTraitAsc
{
    using  Type      = _T;
    using  ObjIDType    = long;
    using  CompareFn = less<Type>;
};

#endif