#ifndef __TYPES_H__
#define __TYPES_H__

using T1=double;
using TX=long;

template <typename _T>
struct BTreeTrait
{
    using  Type      = _T;
    using  ObjIDType    = long;
};

#endif