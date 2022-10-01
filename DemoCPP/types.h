#ifndef __TYPES_H__
#define __TYPES_H__
#include <string.h>
using namespace std;

using T1=double;
using TX=long;

template <typename _T>
struct BTreeTraitDesc
{
    typedef _T Type;
    typedef long ObjIDType;
    typedef greater<Type> CompareFn;
};

template <typename _T>
struct BTreeTraitAsc
{
    typedef _T Type;
    typedef long ObjIDType;
    typedef less<Type> CompareFn;
};

#endif
