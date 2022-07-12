#ifndef __VECTORX_H__  
#define __VECTORX_H__ 

#include <iostream>
using namespace std;

template <typename T>
class VectorX
{
    private:
        T *m_pVector  = nullptr;
        size_t m_size = 0;
    public:
    VectorX(size_t size) : m_size(size) 
    {   create();
    }
    private:
    void create()
    {   destroy();
        m_pVector = new T[m_size];
    }
    void destroy()
    {
        delete [] m_pVector;
        m_pVector = nullptr;
    }
public:
    void init()
    {
        for(auto i=0; i < m_size ; ++i )
        {   m_pVector[i]      = i*i;    }
    }
    void print(ostream &os)
    {   for(auto i=0; i < m_size ; ++i )
        {   os << "m_pVector+"   << i << "=" <<m_pVector+i<< " val=" << m_pVector[i] << ", " << *(m_pVector + i) 
               << " &m_pVector[" << i << "]=" << &m_pVector[i] << "(" << m_pVector+i << ")" << endl;

        }
    }
};

template <typename T>
ostream &operator<<(ostream &os, VectorX<T> &vi)
{
    vi.print(os);
    return os;
}

#endif