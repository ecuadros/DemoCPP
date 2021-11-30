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

#endif