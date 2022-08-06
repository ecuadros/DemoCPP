#ifndef __OPERACION_ESPECIAL_H__  // # es una DIRECTIVAs al PreCOMPILADOR
#define __OPERACION_ESPECIAL_H__ 

template <typename T>
class OperacionEspecial
{
  public:
      void operator()(T &n)
      {
        n *= n;
      }
};

template <typename T>
class SumarIndices
{
    public:
    size_t plus1 = 0, plus2 = 0, n1 = 1, n2 = 1, A = 0;
    T operator()(size_t fil, size_t col)
    {
        return static_cast<T>(fil*n1 + col*n2 + plus1 + plus2*A);
    }
};

#endif